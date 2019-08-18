#[macro_use]
extern crate neon;

extern crate dirs;

use neon::prelude::*;

const vec!: String = [""]

fn hello(mut cx: FunctionContext) -> JsResult<JsString> {
    Ok(cx.string("hello node"))
}

fn load_folders(mut cx: FunctionContext) -> JsResult<JsString> {
    let mut url: String = "".to_string();

    let path_buf = dirs::audio_dir().unwrap();
    let mut folders = Vec::new();
    folders.push(path_buf);
    let mut folder_index: usize = 0;
    while folder_index < folders.len() {
        for entry in folders[folder_index].read_dir().expect("read_dir call failed") {
            if let Ok(entry) = entry {
                if entry.path().is_dir() {
                    folders.push(entry.path());
                }

                else if entry.path().is_file() {
                    if ALLOWED_TYPES.contains(&&entry.path().extension().unwrap().to_string_lossy().to_mut()[..]) {
                        println!("{:?}", entry.path());
                        url = entry.path().to_str().unwrap().to_string();
                    }
                }
            }
        }

        folder_index += 1;
    }
    Ok(cx.string(format!("{:?}", folders)))
}

register_module!(mut cx, {
    cx.export_function("hello", hello);
    cx.export_function("loadFolderse", load_folders);
    Ok(())
});
