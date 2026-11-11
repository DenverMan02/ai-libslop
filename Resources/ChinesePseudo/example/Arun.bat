adb shell am force-stop --user 0 com.popcap.pvz2cthddev
adb push obj/local/arm64-v8a/libSrcExt.so /data/local/tmp
REM adb push libs/arm64-v8a/libSrcExt.so /data/local/tmp
adb shell "su -c cp /data/local/tmp/libSrcExt.so $(su -c find /data/app -name com.popcap.pvz2cthddev*)/lib/arm64/libSrcExt.so"
adb shell am start --user 0 -n com.popcap.pvz2cthddev/com.popcap.SexyAppFramework.SexyAppFrameworkActivity
REM adb shell "logcat --pid $(pidof com.popcap.pvz2cthddev)"
REM adb shell "logcat -s SrcExt:*"
REM adb shell "rm -rf /data/data/com.popcap.pvz2cthddev/files/*