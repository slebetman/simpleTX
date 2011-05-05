#! /usr/bin/env tclsh

if {![file exists backup.hex] || ![file exists txmod.hex]} exit

package require fileparse

set trim_data {}

eachline x backup.hex {
	if {[string match :104* $x]} {
		lappend trim_data $x
	}
}

set txmod {}

eachline x txmod.hex {
	if {![string match :104* $x]} {
		lappend txmod $x
	}
}

set last [lindex [lsearch -all $txmod :10*] end]
incr last

set txmod [linsert $txmod $last {*}$trim_data]

burp txmod.hex "[join $txmod \n]\n"

