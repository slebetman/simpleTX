#! /usr/bin/env tclsh

package require fileparse

set eeprom {}

eachline x [lindex $argv 0] {
	if {[regexp {^:104[\dA-F]{5}([\dA-F]+)[\dA-F]{2}$} $x -> hex]} {
		foreach {- byte} [regexp -inline -all {([\dA-F]{2})00} $hex] {
			lappend eeprom $byte
		}
	}
}

foreach {a b c d e f g h} $eeprom {
	puts "_EEPROM_DATA(0x${a},0x${b},0x${c},0x${d},0x${e},0x${f},0x${g},0x${h});"
}