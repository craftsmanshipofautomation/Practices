#include "sftp-client.h"

SSHSession::SSHSession(std::string &host, int port, std::string &username, std::string &password)
    : username_(username), password_(password)
{
    int verbosity = SSH_LOG_PROTOCOL;
    ssh_options_set(sshrc_.session(), SSH_OPTIONS_HOST, host.c_str());
    ssh_options_set(sshrc_.session(), SSH_OPTIONS_LOG_VERBOSITY, &verbosity);
    ssh_options_set(sshrc_.session(), SSH_OPTIONS_PORT, &port);
    if (SSH_OK != ssh_connect(sshrc_.session()))
        throw SFTPException("SSH session failed to connect");
    AuthenticateWithPassword();
}

SSHSession::~SSHSession()
{
    ssh_disconnect(sshrc_.session());
}

int SSHSession::VerifyKnownServer()
{
    enum ssh_known_hosts_e state;
    unsigned char *hash = NULL;
    ssh_key srv_pubkey = NULL;
    size_t hlen;
    char buf[10];
    char *hexa;
    char *p;
    int cmp;
    int rc;

    rc = ssh_get_server_publickey(sshrc_.session(), &srv_pubkey);
    if (rc < 0)
    {
        return -1;
    }

    rc = ssh_get_publickey_hash(srv_pubkey,
                                SSH_PUBLICKEY_HASH_SHA1,
                                &hash,
                                &hlen);
    ssh_key_free(srv_pubkey);
    if (rc < 0)
    {
        return -1;
    }

    state = ssh_session_is_known_server(sshrc_.session());
    switch (state)
    {
    case SSH_KNOWN_HOSTS_OK:
        /* OK */

        break;
    case SSH_KNOWN_HOSTS_CHANGED:
        fprintf(stderr, "Host key for server changed: it is now:\n");
        ssh_print_hexa("Public key hash", hash, hlen);
        fprintf(stderr, "For security reasons, connection will be stopped\n");
        ssh_clean_pubkey_hash(&hash);

        return -1;
    case SSH_KNOWN_HOSTS_OTHER:
        fprintf(stderr, "The host key for this server was not found but an other"
                        "type of key exists.\n");
        fprintf(stderr, "An attacker might change the default server key to"
                        "confuse your client into thinking the key does not exist\n");
        ssh_clean_pubkey_hash(&hash);

        return -1;
    case SSH_KNOWN_HOSTS_NOT_FOUND:
        fprintf(stderr, "Could not find known host file.\n");
        fprintf(stderr, "If you accept the host key here, the file will be"
                        "automatically created.\n");

        /* FALL THROUGH to SSH_SERVER_NOT_KNOWN behavior */

    case SSH_KNOWN_HOSTS_UNKNOWN:
        hexa = ssh_get_hexa(hash, hlen);
        fprintf(stderr, "The server is unknown. Do you trust the host key?\n");
        fprintf(stderr, "Public key hash: %s\n", hexa);
        ssh_string_free_char(hexa);
        ssh_clean_pubkey_hash(&hash);

        /// 就当输入了 yes
        /// p = fgets(buf, sizeof(buf), stdin);
        /// if (p == NULL)
        /// {
        ///     return -1;
        /// }
        /// cmp = strncasecmp(buf, "yes", 3);
        /// if (cmp != 0)
        /// {
        ///     return -1;
        /// }

        rc = ssh_session_update_known_hosts(sshrc_.session());
        if (rc < 0)
        {
            fprintf(stderr, "Error %s\n", std::strerror(errno));
            return -1;
        }

        break;
    case SSH_KNOWN_HOSTS_ERROR:
        fprintf(stderr, "Error %s", ssh_get_error(sshrc_.session()));
        ssh_clean_pubkey_hash(&hash);
        return -1;
    }

    ssh_clean_pubkey_hash(&hash);
    return 0;
}

void SSHSession::AuthenticateWithPassword()
{
    int rc = ssh_userauth_password(sshrc_.session(), NULL, password_.c_str());
    if (rc != SSH_AUTH_SUCCESS)
        throw SFTPException("Error authenticating with password");
}

SFTPSession::SFTPSession(SSHSession &ss)
    : sftprc_(ss)
{
    if (sftp_init(sftprc_.session()) != SSH_OK)
    {
        throw SFTPException("SFTPSession Failed to init");
    }
}

SFTPSession::~SFTPSession()
{
}

SFTPClient::SFTPClient(std::string &host, int port, std::string &username, std::string &password)
    : ssh_ss_(host, port, username, password), sftp_ss_(ssh_ss_)
{
}

SFTPClient::~SFTPClient()
{
}

void SFTPClient::ReadSync(std::string src, std::string dest)
{
    char buffer[MAX_XFER_BUF_SIZE];
    int nbytes, nwritten, rc;
    STFPFile file(sftp_ss_, src, O_RDONLY, dest, O_CREAT | O_RDWR | O_TRUNC);

    for (;;)
    {
        nbytes = sftp_read(file.remote(), buffer, sizeof(buffer));
        if (nbytes == 0)
        {
            break; // EOF
        }
        else if (nbytes < 0)
            throw SFTPException("Error while reading remote file");

        nwritten = write(file.local(), buffer, nbytes);
        if (nwritten != nbytes)
        {
            throw SFTPException("Error writing");
        }
    }

    if (rc != SSH_OK)
        throw SFTPException("Can't close the read file");
}

void SFTPClient::WriteSync(std::string src, std::string dest)
{
    int rc, nwritten, nbytes;
    char buffer[MAX_XFER_BUF_SIZE];

    STFPFile file(sftp_ss_, dest, O_CREAT | O_RDWR | O_TRUNC, src, O_RDONLY);

    for (;;)
    {
        nbytes = read(file.local(), buffer, sizeof(buffer));
        if (nbytes == 0)
        {
            break; // EOF
        }
        else if (nbytes < 0)
            throw SFTPException("Error while reading local file");

        nwritten = sftp_write(file.remote(), buffer, sizeof(buffer));
        if (nwritten != nbytes)
        {
            throw SFTPException("Error writing");
        }
    }
}
