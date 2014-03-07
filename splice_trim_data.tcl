#! /usr/bin/env tclsh

if {![file exists backup_hex] || ![file exists txmod.hex]} exit

set trim_data {:020000040000FA}

proc eachline {var filename script} {
	set f [open $filename]
	set txt [read $f]
	close $f
	
	upvar 1 $var line
	
	foreach line [split $txt "\n"] {
		uplevel 1 $script
	}
}

proc burp {filename data} {
	set f [open $filename w]
	puts -nonewline $f $data
	close $f
}

eachline x backup_hex {
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

