/*
 * stubs/vendor_stubs.c
 *
 * Weak fallback definitions for vendor (Huawei / Qualcomm) hooks that are
 * referenced unconditionally from generic driver code, but whose real
 * implementations live in .c files gated behind CONFIG_ options that are
 * disabled in this defconfig.
 *
 * Every symbol here is marked __weak: if you ever enable the config that
 * provides the real implementation, the real (strong) symbol will silently
 * take priority at link time and this file becomes a no-op for it. That
 * makes this file safe to leave in the tree permanently.
 *
 * IMPORTANT: the exact return type / argument list of each function below
 * is a best-effort guess based on the symbol name and calling convention
 * only -- I could not fetch the real extern declarations for this tree.
 * Run scripts/check_vendor_stubs.sh (added alongside this file) against
 * your actual checked-out source BEFORE building: it greps your tree for
 * each symbol's real declaration and prints it next to the guess below so
 * you can fix any mismatch in a couple of minutes. On arm64 a mismatched
 * *argument* (e.g. fewer params than the real prototype) is harmless --
 * unused incoming registers are simply never read. A mismatched *return
 * type* (e.g. stubbing an int-returning function as void) is the case to
 * double check, since the caller may read a stale register as the result.
 */

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/compiler.h>

/* --- drivers/soc/qcom/watchdog_v2.c, mmc/core/core.c, kernel/panic.c,
 *     platform/msm/qpnp-power-on.c : boot-fail-flag subsystem ---------- */
int __weak qcom_set_boot_fail_flag(int flag)
{
	return 0;
}

int __weak check_bootfail_inject(void)
{
	return 0;
}

int __weak qcom_get_boot_stage(void)
{
	return 0;
}

int __weak bfmr_has_been_enabled(void)
{
	return 0;
}

int __weak boot_fail_err(int err)
{
	return 0;
}

/* init/main.c, security/security.c, drivers/tty/tty_io.c */
void __weak bfm_set_boot_stage(unsigned int stage)
{
}

/* init/main.c */
void __weak hwboot_fail_init_struct(void)
{
}

/* drivers/power/reset/msm-poweroff.c */
void __weak hwboot_clear_magic(void)
{
}

/* kernel/time/timekeeping.c */
void __weak boot_ats_task_wakeup(void)
{
}

/* --- drivers/soc/qcom/socinfo.c ---------------------------------------- */
int __weak get_sensor_info_of_product_name(char *buf, int len)
{
	if (buf && len > 0)
		buf[0] = '\0';
	return 0;
}

/* --- drivers/hw_fac_info/config_interface.c, camera, power/smb1360 ----- */
int __weak app_info_set(const char *name, const char *value)
{
	return 0;
}

/* --- drivers/misc/qseecom.c : referenced as a plain flag (not called) -- */
int snr_flag;

/* --- drivers/usb/gadget/{composite,android}.c, function/f_mass_storage.c */
int __weak hw_usb_port_switch_request(int mode)
{
	return 0;
}

void __weak hw_usb_handle_host_time(void)
{
}

void __weak *hw_usb_get_device(void)
{
	return NULL;
}

int __weak hw_rwswitch_create_device(void *dev)
{
	return 0;
}

void __weak hw_usb_sync_host_time_init(void)
{
}

/* --- sound/soc/codecs/{tas2560-regmap,tas2560-calib,msm8x16-wcd,
 *     msm8916-wcd-irq,wcd-mbhc-v2}.c, sound/soc/msm/qdsp6v2/q6afe.c,
 *     sound/soc/msm/msm8952.c : Huawei "DSM" audio diagnostics --------- */
void __weak audio_dsm_report_info(int type, const char *fmt, ...)
{
}

void __weak audio_dsm_report_num(int type, int num)
{
}

int __weak audio_dsm_register(void *ops)
{
	return 0;
}

void __weak *hw_get_registered_codec(void)
{
	return NULL;
}

/* --- sound/soc/codecs/msm8x16-wcd.c : referenced as a plain flag ------- */
int mic1_differential_mode_enable;
