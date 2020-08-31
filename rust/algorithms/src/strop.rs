pub fn reverse_words(s: String) -> String {
    let mut news = String::new();
    let len = s.len();
    news.reserve(len);
    let mut h: usize = 0;
    let mut t: usize = 0;
    let mut c = s.char_indices().peekable();
    let mut unfinished = true;

    loop {
        loop {
            if let Some((n, i)) = c.peek() {
                if *i == ' ' {
                    c.next();
                } else {
                    t = *n;
                    break;
                }
            } else {
                unfinished = false;
                c.next();
                break;
            }
        }

        if !unfinished {
            break;
        }
        h = t;
        loop {
            if let Some((_, i)) = c.peek() {
                if *i != ' ' {
                    c.next();
                    t += 1;
                } else {
                    c.next();
                    break;
                }
            } else {
                unfinished = false;
                break;
            }
        }

        for r in s[h..t].chars().rev() {
            news.push(r);
        }

        if !unfinished {
            break;
        } else {
            news.push(' ');
        }
    }
    news
}
