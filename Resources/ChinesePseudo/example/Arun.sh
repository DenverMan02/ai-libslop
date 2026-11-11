adb shell am force-stop --user 0 com.popcap.pvz2cthddev
adb shell "su -c pkill gdbserver -9"
adb push obj/local/arm64-v8a/libSrcExt.so /data/local/tmp
#adb push libs/arm64-v8a/libSrcExt.so /data/local/tmp
adb shell "su -c cp /data/local/tmp/libSrcExt.so \$(su -c find /data/app -name com.popcap.pvz2cthddev*)/lib/arm64/libSrcExt.so"
adb shell am start --user 0 -n com.popcap.pvz2cthddev/com.popcap.SexyAppFramework.SexyAppFrameworkActivity
sleep 1
adb shell "su -c nohup /data/local/tmp/gdb-static-full-aarch64/gdbserver --attach 0.0.0.0:1234 \$(pidof com.popcap.pvz2cthddev) > /dev/null 2>&1 &"
# adb shell "logcat --pid $(pidof com.popcap.pvz2cthddev)"
# adb shell "logcat -s SrcExt:*"
# adb shell "rm -rf /data/data/com.popcap.pvz2cthddev/files/*