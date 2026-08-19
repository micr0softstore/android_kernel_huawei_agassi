export CROSS_COMPILE="/home/msstore/android_kernel_huawei_agassi/toolchain/bin/aarch64-linux-android-"
export ARCH=arm64

make O=out agassi_defconfig -j16
make O=out -j16
