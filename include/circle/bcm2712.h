//
// bcm2712.h
//
// Memory I/O addresses of peripherals, which were introduced
// with the Raspberry Pi 5
//
// Circle - A C++ bare metal environment for Raspberry Pi
// Copyright (C) 2023  R. Stange <rsta2@o2online.de>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
#ifndef _circle_bcm2712_h
#define _circle_bcm2712_h

#if RASPPI >= 5

#include <circle/bcm2835.h>

//
// Second level interrupt controller (RP1)
//
#define ARM_RP1_INTC		0x1F00108000UL

//
// General Purpose I/O #0 (RP1)
//
#define ARM_GPIO0_IO_BASE	0x1F000D0000UL		// IO_BANK0
#define ARM_GPIO0_PADS_BASE	0x1F000F0000UL		// PADS_BANK0

//
// General Purpose I/O #2
//
#define ARM_GPIO2_BASE		(ARM_IO_BASE + 0x1517C00)

#define ARM_GPIO2_DATA0		(ARM_GPIO2_BASE + 0x04)
#define ARM_GPIO2_IODIR0	(ARM_GPIO2_BASE + 0x08)

//
// Reset controller
//
#define ARM_RESET_BASE		0x1001504318UL
#define ARM_RESET_END		(ARM_RESET_BASE + 0x2F)

//
// PCIe rescal reset controller
//
#define ARM_RESET_RESCAL_BASE	0x1000119500UL
#define ARM_RESET_RESCAL_END	(ARM_RESET_RESCAL_BASE + 0x0F)

#endif

#endif
