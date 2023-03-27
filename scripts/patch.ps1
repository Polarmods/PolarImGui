$ip = "127.0.0.1"
$port = "5555"
$lib = "libnative-lib.so"
$app = "com.innersloth.spacemafia"
$mod_apk_name = "app-debug.apk"
$mod_apk_path = "../app/build/outputs/apk/debug/"
$mod_arch = "arm" #arm or arm64
$mod_type = "armeabi-v7a" #arm64-v8a or armeabi-v7a
$mod_lib_path = "mod/lib/"+$mod_type+"/"+$lib

7z x $mod_apk_path$mod_apk_name -omod -y

adb connect $ip":"$port

$APP_PATH = (adb -s $ip":"$port shell pm path $app | Out-String).Trim().Replace("package:","").Replace("/base.apk","")

adb -s $ip":"$port push $mod_lib_path /sdcard/$lib

adb -s $ip":"$port shell su root mv /sdcard/$lib $APP_PATH/lib/$mod_arch/$lib
adb -s $ip":"$port shell su root chown system:system $APP_PATH/lib/$mod_arch/$lib
adb -s $ip":"$port shell su root chmod 755 $APP_PATH/lib/$mod_arch/$lib



adb -s $ip":"$port shell "cd $APP_PATH/lib/$mod_arch;ls -la"

pause