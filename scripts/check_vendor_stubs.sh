#!/bin/bash
# Run this from the top of your kernel tree AFTER applying the vendor-stubs
# patches and BEFORE building. For every symbol stubbed in
# stubs/vendor_stubs.c, it greps your real tree for the extern declaration
# so you can eyeball it against the guessed stub and fix any mismatch by
# hand (return type is what matters most -- see the comment header in
# stubs/vendor_stubs.c for why argument-count mismatches are low risk on
# arm64).
#
# Usage: bash scripts/check_vendor_stubs.sh

set -u

SYMS=(
	qcom_set_boot_fail_flag check_bootfail_inject qcom_get_boot_stage
	bfmr_has_been_enabled boot_fail_err bfm_set_boot_stage
	hwboot_fail_init_struct hwboot_clear_magic boot_ats_task_wakeup
	get_sensor_info_of_product_name app_info_set snr_flag
	hw_usb_port_switch_request hw_usb_handle_host_time hw_usb_get_device
	hw_rwswitch_create_device hw_usb_sync_host_time_init
	audio_dsm_report_info audio_dsm_report_num audio_dsm_register
	hw_get_registered_codec mic1_differential_mode_enable
)

for s in "${SYMS[@]}"; do
	echo "==== $s ===="
	# Look for the extern/plain declaration in headers first (most likely
	# spot), then fall back to any non-stub occurrence in the whole tree.
	hit=$(grep -rn --include='*.h' -E "[[:space:];]$s[[:space:]]*\(|[[:space:]]$s[[:space:]]*;|[[:space:]]$s\[" \
		--exclude-dir=stubs . 2>/dev/null | head -3)
	if [ -z "$hit" ]; then
		hit=$(grep -rn -E "[[:space:];]$s[[:space:]]*\(" \
			--exclude-dir=stubs . 2>/dev/null | grep -v '/vendor_stubs\.c:' | head -3)
	fi
	if [ -n "$hit" ]; then
		echo "$hit"
	else
		echo "  (no declaration found by this heuristic -- check manually, e.g. 'grep -rn \"$s\" .')"
	fi
	echo
done
