import os
import fnmatch
import re


class Injector(object):
    METHOD_PATTEN = re.compile(
    r"^(?P<id>\w+)\s+(?P<clsn>\w+)(?P<colon>::)(?P<fn>\w+)(?P<args>\(.*?\))\s*{$")
    FUNCTION_PATTEN = re.compile(
    r"^(?P<id>\w+)\s+(?P<fn>\w+)(?P<args>\(.*\))\s*{$")
    @staticmethod
    def find_files(directory, pattern):
        for root, dirs, files in os.walk(directory):
            for basename in files:
                if fnmatch.fnmatch(basename, pattern):
                    filename = os.path.join(root, basename)
                    yield filename
    @staticmethod
    def is_function(line):
        matches = Injector.FUNCTION_PATTEN.match(line)
        if matches is None:
            # print("NO matches")
            return False, None, None, None
        identifier = matches.group("id")
        function_name = matches.group("fn")
        args = matches.group("args")
        return True, identifier, function_name, args

    @staticmethod
    def is_method(line):
        matches = Injector.METHOD_PATTEN.match(line)
        if matches is None:
            # print("NO matches")
            return False, None, None, None, None
        identifier = matches.group("id")
        class_name = matches.group("clsn")
        function_name = matches.group("fn")
        args = matches.group("args")
        return True, identifier, class_name, function_name, args

    @staticmethod
    def is_possible(line):
        if line and line[0].isalpha():
            return True
        return False

    @staticmethod
    def _inject(_file, _log_str):
        new_file = _file+"_new"
        #print new_file
        with open(_file, "r", encoding = "ISO-8859-1") as f ,open(new_file, "w") as newf:
            for line in f:
                newf.write(line)
                if Injector.is_possible(line):
                    method_found, id, clsn, fn, args = Injector.is_method(line)
                    if method_found:
                        #print("line = {line}, id = {id}, clsn = {clsn}, fn = {fn}, args = {args}".format(line=line,id=id,clsn=clsn, fn=fn, args=args))
                        newf.write(_log_str)
                    else:
                        function_found, id, fn, args = Injector.is_function(line)
                        if function_found:
                            #print("line = {line}, id = {id}, fn = {fn}, args = {args}".format(line=line,id=id, fn=fn, args=args))
                            newf.write(_log_str)
        os.remove(_file)
        os.rename(new_file, _file)

    def __init__(self, _file, _log_str):
        self._file = _file
        self._log_str = _log_str
    def inject(self):
        Injector._inject(self._file, self._log_str)

if __name__ == "__main__":
    import sys
    _file = sys.argv[1]
    #log_str = sys.argv[2]
    log_str = ""
    if log_str == "":
        slash_pos = _file.rfind("/")
        _fileN = _file[slash_pos+1:]
        log_str = 'LOGD(TAG, "file: {}, function: %s, line: %d", __FUNCTION__, __LINE__);\n'.format(_fileN)
    inj = Injector(_file, log_str)
    inj.inject()