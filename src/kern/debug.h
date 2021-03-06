/*
 * Copyright (c) 2000-2007 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 * 
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 * 
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 * 
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 * 
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */

#ifndef _KERN_DEBUG_H_
#define _KERN_DEBUG_H_

#include <sys/cdefs.h>
#include <stdint.h>

struct thread_snapshot {
	uint32_t		snapshot_magic;
	uint32_t		nkern_frames;
	uint32_t		nuser_frames;
	uint64_t		wait_event;
	uint64_t		continuation;
	uint64_t		thread_id;
	uint64_t		user_time;
	uint64_t		system_time;
	int32_t			state;
	int32_t			sched_pri;		// scheduled (current) priority		*
	int32_t			sched_flags;	// scheduler flags					*
	char			ss_flags;
} __attribute__((packed));

struct task_snapshot {
	uint32_t		snapshot_magic;
	int32_t			pid;
	uint32_t		nloadinfos;
	uint64_t		user_time_in_terminated_threads;
	uint64_t		system_time_in_terminated_threads;
	int				suspend_count; 
	int				task_size;		// pages
	int				faults;			// number of page faults
	int				pageins;		// number of actual pageins
	int				cow_faults;		// number of copy-on-write faults
char			spare[227];
	char			ss_flags;
	char			p_comm[17];
} __attribute__((packed));

struct mem_snapshot {
	uint32_t		snapshot_magic;
	uint32_t		free_pages;
	uint32_t		active_pages;
	uint32_t		inactive_pages;
	uint32_t		purgeable_pages;
	uint32_t		wired_pages;
	uint32_t		speculative_pages;
	uint32_t		throttled_pages;
} __attribute__((packed));

struct mem_and_io_snapshot {
	uint32_t		snapshot_magic;
	uint32_t		free_pages;
	uint32_t		active_pages;
	uint32_t		inactive_pages;
	uint32_t		purgeable_pages;
	uint32_t		wired_pages;
	uint32_t		speculative_pages;
	uint32_t		throttled_pages;
	int				busy_buffer_count;
	uint32_t		pages_wanted;
	uint32_t		pages_reclaimed;
	uint8_t			pages_wanted_reclaimed_valid; // did mach_vm_pressure_monitor succeed?
} __attribute__((packed));


enum {
	kUser64_p = 0x1,
	kKernel64_p = 0x2,
	kHasDispatchSerial = 0x4,
	kTerminatedSnapshot = 0x8,
	kPidSuspended = 0x10,  // true for suspended task
	kFrozen = 0x20         // true for hibernated task (along with pidsuspended)
};

#define VM_PRESSURE_TIME_WINDOW 5 /* seconds */

enum {
	STACKSHOT_GET_DQ = 0x1,
	STACKSHOT_SAVE_LOADINFO = 0x2,
	STACKSHOT_GET_GLOBAL_MEM_STATS = 0x4
};

#define STACKSHOT_THREAD_SNAPSHOT_MAGIC         0xfeedface
#define STACKSHOT_TASK_SNAPSHOT_MAGIC           0xdecafbad
#define STACKSHOT_MEM_SNAPSHOT_MAGIC			0xabcddcba
#define STACKSHOT_MEM_AND_IO_SNAPSHOT_MAGIC     0xbfcabcde

#endif  /* _KERN_DEBUG_H_ */
