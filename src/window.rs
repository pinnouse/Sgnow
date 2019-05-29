
fn inline_style(s: &str) -> String {
    format!(r#"<style type="type/css">{}</style>"#, s);
}

fn inline_script(s: &str) -> String {
    format!(r#"<script type="text/javascript">{}</script>"#, s);
}