#! /usr/bin/env wish

package require Tk

. configure -padx 10 -pady 10;

set currentModel 0
set modelName ""
array set modelTrim {}
array set modelScaling {}
array set outputMap {}
array set mixInputs {}
array set mixOutputs {}
array set mixScaling {}
array set mixExpo {}
array set mixReverse {}
set data {}

proc main {} {
	if {[catch {open "backup_hex" r} f]} {
		pack [label .l -text "Error: $f" -padx 20 -pady 10]
		pack [button .b -text "OK" -command {exit}]
	} else {
		set raw [read $f]
		close $f

		set ::data [parseHexFile $raw]
		set ::currentModel [expr [lindex $::data 255]]
		parseModel $::data

		pack [frame .bottom -pady 5] -side bottom -fill x
		pack [button .bottom.save -text "Save" -command [subst -nocommands {
			set rawSave [formatHexFile "$raw" \$::data]
			saveFile \$rawSave
			exit
		}]] -anchor e
		
		pack [frame .cfg -padx 10 -pady 2] \
			-side left -anchor nw \
			-expand 1 -fill y

		pack [frame .hex -borderwidth 1 -relief solid] \
			-side right -anchor n

		for {set i 0} {$i<16} {incr i} {
			pack [label .hex.row$i -bg white -font TkFixedFont]
		}

		displayHex
		set currentModel [expr [lindex $::data 255]]

		grid [label .cfg.lmodel -text "Selected Model:"] \
			-row 0 -column 0 -sticky w

		grid [menubutton .cfg.model \
			-menu .cfg.model.select \
			-bg white \
			-relief sunken \
			-textvariable ::currentModel
		] -row 0 -column 1 -sticky w

		menu .cfg.model.select -tearoff false -bg white

		for {set i 0} {$i < 5} {incr i} {
			.cfg.model.select add command -label $i -command [subst {
				set ::currentModel $i
				lset ::data 255 $i
				parseModel \$::data
			}]
		}

		grid [label .cfg.lname -text "Model Name:"] \
			-row 0 -column 2 -sticky w

		grid [entry .cfg.name -width 10 \
			-validate key \
			-validatecommand {
				expr {[string length "%P"] <= 10}
			} \
			-textvariable ::modelName
		] -row 0 -column 3 -sticky w

		trace add variable ::modelName write displayHex

		grid [ttk::separator .cfg.h1 -orient horizontal] \
			-columnspan 4 \
			-sticky ew \
			-pady 5
		
		for {set i 0} {$i<4} {incr i} {
			grid [label .cfg.ltrim$i -text "Trim$i:"] \
				-row [expr {2+$i}] -column 0 -sticky e

			grid [entry .cfg.trim$i -width 5 \
				-textvariable ::modelTrim($i)
			] -row [expr {2+$i}] -column 1 -sticky w

			trace add variable ::modelTrim($i) write displayHex
		}

		for {set i 0} {$i<4} {incr i} {
			grid [label .cfg.lscale$i -text "Scale$i:"] \
				-row [expr {2+$i}] -column 2 -sticky e

			grid [entry .cfg.scale$i -width 5 \
				-textvariable ::modelScaling($i)
			] -row [expr {2+$i}] -column 3 -sticky w

			trace add variable ::modelScaling($i) write displayHex
		}

		grid [ttk::separator .cfg.h2 -orient horizontal] \
			-columnspan 4 \
			-sticky ew \
			-pady 5

		grid [label .cfg.outlabel -text "Output map:"] \
			-row 7 -column 0 \
			-sticky w 

		for {set i 0} {$i<3} {incr i} {
			grid [label .cfg.lout$i -text "CH$i:"] \
				-row [expr {8+$i}] -column 0 -sticky e

			grid [entry .cfg.out$i -width 5 \
				-textvariable ::outputMap($i)
			] -row [expr {8+$i}] -column 1 -sticky w

			trace add variable ::outputMap($i) write displayHex
		}

		for {set i 3} {$i<6} {incr i} {
			grid [label .cfg.lout$i -text "CH$i:"] \
				-row [expr {8+$i-3}] -column 2 -sticky e

			grid [entry .cfg.out$i -width 5 \
				-textvariable ::outputMap($i)
			] -row [expr {8+$i-3}] -column 3 -sticky w

			trace add variable ::outputMap($i) write displayHex
		}

		grid [ttk::separator .cfg.h3 -orient horizontal] \
			-columnspan 4 \
			-sticky ew \
			-pady 5

		grid [label .cfg.mixlabel -text "Mixes:"] \
			-sticky w 

		grid [frame .cfg.mix] \
			-columnspan 4 -sticky ew

		for {set i 0} {$i<10} {incr i} {
			grid [label .cfg.mix.lname$i -text "$i - "] \
				-row $i -column 0 -sticky e

			grid [label .cfg.mix.linput$i -text "In:"] \
				-row $i -column 1 -sticky e

			grid [entry .cfg.mix.input$i -width 2 \
				-textvariable ::mixInputs($i)
			] -row $i -column 2 -sticky w

			trace add variable ::mixInputs($i) write displayHex

			grid [label .cfg.mix.loutput$i -text " Out:"] \
				-row $i -column 3 -sticky e

			grid [entry .cfg.mix.output$i -width 2 \
				-textvariable ::mixOutputs($i)
			] -row $i -column 4 -sticky w

			trace add variable ::mixOutputs($i) write displayHex

			grid [label .cfg.mix.lscale$i -text " Scale:"] \
				-row $i -column 5 -sticky e

			grid [entry .cfg.mix.scale$i -width 3 \
				-textvariable ::mixScaling($i)
			] -row $i -column 6 -sticky w

			trace add variable ::mixScaling($i) write displayHex

			grid [label .cfg.mix.lexpo$i -text " Expo:"] \
				-row $i -column 7 -sticky e

			grid [entry .cfg.mix.expo$i -width 3 \
				-textvariable ::mixExpo($i)
			] -row $i -column 8 -sticky w

			trace add variable ::mixExpo($i) write displayHex

			grid [checkbutton .cfg.mix.lreverse$i -text "Reverse" \
				-variable ::mixReverse($i)
			] -row $i -column 9 -sticky e

			trace add variable ::mixReverse($i) write displayHex
		}
	}
}

proc setDataByte {i val} {
	set idx [expr {($::currentModel*51)+$i}]
	lset ::data  $idx $val
}

proc getDataByte {i} {
	set idx [expr {($::currentModel*51)+$i}]
	return [lindex $::data  $idx]
}

proc forEachDataBytes {start end var idx callback} {
	upvar $var v
	upvar $idx i
	for {set i 0} {$i < ($end-$start)} {incr i} {
		set v [getDataByte [expr {$i+$start}]]
		uplevel $callback
	}
}

proc parseModel {data} {
	set name ""
	set modelTrim {}
	set modelScaling {}
	set outputMap {}
	set mixInputs {}
	set mixOutputs {}
	set mixScaling {}
	set mixExpo {}
	set mixReverse {}

	forEachDataBytes 0 10 x i {
		if {$x != 0xff && $x != 0} {
			append name [format %c $x]
		}
	}

	forEachDataBytes 10 14 x i {
		set trim [expr {$x*4}]

		# Handle sign bit:
		if {$trim & 0x0200} {
			set trim [expr {$trim & (~0x0200)}]
			set trim -[expr {(~$trim+1)&0xff}]
		}

		lappend modelTrim $i $trim
	}
	forEachDataBytes 14 18 x i {
		lappend modelScaling $i [expr $x]
	}
	forEachDataBytes 18 21 x i {
		set a [expr {$x & 0x0f}]
		set b [expr {($x >> 4) & 0x0f}]

		if {$a == 0xf} {
			lappend outputMap [expr {$i*2}] -
		} else {
			lappend outputMap [expr {$i*2}] [expr $a]
		}

		if {$b == 0xf} {
			lappend outputMap [expr {($i*2)+1}] -
		} else {
			lappend outputMap [expr {($i*2)+1}] [expr $b]
		}
	}
	for {set m 0} {$m < 10} {incr m} {
		set offset [expr {($m*3)+21}]
		set ch [getDataByte $offset]

		set in [expr {($ch >> 4) & 0x0f}]
		set out [expr {$ch & 0x0f}]
		if {$out == 0xf} {
			set out -
		}

		set scaling [getDataByte [expr {$offset+1}]]
		set reverse [expr {!!($scaling & 0x80)}]
		set scaling [expr {$scaling & 0x7f}]

		set expo [expr [getDataByte [expr {$offset+2}]]]

		lappend mixInputs $m $in
		lappend mixOutputs $m $out
		lappend mixScaling $m $scaling
		lappend mixReverse $m $reverse
		lappend mixExpo $m $expo
	}

	set ::modelName $name
	array set ::modelTrim $modelTrim
	array set ::modelScaling $modelScaling
	array set ::outputMap $outputMap
	array set ::mixInputs $mixInputs
	array set ::mixOutputs $mixOutputs
	array set ::mixScaling $mixScaling
	array set ::mixExpo $mixExpo
	array set ::mixReverse $mixReverse
}

proc displayHex {args} {
	# copy name:
	if {[string length $::modelName]} {
		set name [split $::modelName ""]
		for {set i 0} {$i < 10} {incr i} {
			if {$i < [llength $name]} {
				set n [lindex $name $i]
				setDataByte $i [scan $n %c]
			} elseif {$i == [llength $name]} {
				setDataByte $i 0
			} else {
				setDataByte $i 0xff
			}
		}
	} else {
		for {set i 0} {$i < 10} {incr i} {
			setDataByte $i 0xff
		}
	}

	# copy trim
	for {set i 0} {$i<4} {incr i} {
		set trim $::modelTrim($i)
		if {[string is integer -strict $trim]} {
			setDataByte [expr {$i+10}] [expr {($trim/4)&0xff}]
		}
	}

	# copy scaling
	for {set i 0} {$i<4} {incr i} {
		set scaling $::modelScaling($i)
		if {[string is integer -strict $scaling]} {
			setDataByte [expr {$i+14}] [expr {$scaling&0xff}]
		}
	}

	# copy output map
	for {set i 0} {$i<3} {incr i} {
		set a $::outputMap([expr {$i*2}])
		set b $::outputMap([expr {($i*2)+1}])

		if {$a == "-"} {
			set a 0xf
		}

		if {$b == "-"} {
			set b 0xf
		}

		if {
			[string is integer -strict $a] &&
			[string is integer -strict $b]
		} {
			setDataByte [expr {$i+18}] [expr {
				($a & 0x0f) | 
				(($b << 4) & 0xf0)
			}]
		}
	}

	# copy mixes
	for {set m 0} {$m < 10} {incr m} {
		set offset [expr {($m*3)+21}]

		set in $::mixInputs($m)
		set out $::mixOutputs($m)
		if {$out == "-"} {
			set out 0xf
		}

		if {
			[string is integer -strict $in] &&
			[string is integer -strict $out]
		} {
			set ch [expr {(($in << 4) | ($out & 0xf)) & 0xff}]
			setDataByte $offset $ch
		}

		if {[string is integer -strict $::mixScaling($m)]} {
			set scaling [expr {$::mixScaling($m) & 0xff}]
			if {$::mixReverse($m)} {
				set scaling [expr {$scaling | 0x80}]
			}
			setDataByte [expr {$offset+1}] $scaling
		}

		if {[string is integer -strict $::mixExpo($m)]} {
			setDataByte [expr {$offset+2}] $::mixExpo($m)
		}
	}

	for {set i 0} {$i<16} {incr i} {
		set x {}
		foreach y [lrange $::data [expr {$i*16}] [expr {($i*16)+15}]] {
			lappend x [format %02X $y]
		}
		.hex.row$i configure -text $x
	}
}

proc parseHexLine {line} {
	regexp {^:1000([0-9a-fA-F]{2})00([0-9a-fA-F]{32})} $line - baseAddr hex

	set baseAddr "0x$baseAddr"
	set idx 0
	set digits [split $hex ""]

	set ret {}

	foreach {h l} $digits {
		lappend ret "0x$h$l"
		incr idx
	}

	return $ret
}

proc parseHexFile {raw} {
	set lines [split $raw "\n"]
	set data {}
	set start 0

	foreach line $lines {
		if {$line == ":0200000400F00A"} {
			set start 1
			continue
		}
		if {$line == ":020000040030CA"} {
			set start 0
			continue
		}

		if {$start} {
			if {[regexp {^:1000} $line]} {
				lappend data {*}[parseHexLine $line]
			}
		}
	}

	return $data
}

proc checksum {x} {
	set x [string range $x 3 end]
	set sum 0x0f
	foreach {a b} [split $x ""] {
		set num "0x$a$b"
		incr sum $num
	}
	set sum [expr {((~$sum) & 0xff)}]
	return [format %02X $sum]
}

proc formatHexFile {raw data} {
	set lines [split $raw "\n"]
	set start 0
	set res {}

	foreach line $lines {
		if {$line == ":0200000400F00A"} {
			lappend res $line
			set start 1
			continue
		}

		if {$line == ":020000040030CA"} {
			lappend res $line
			set start 0
			continue
		}

		if {$start} {
			if {[regexp {^:10000000} $line]} {
				for {set i 0} {$i<16} {incr i} {
					set start [expr {$i*16}]
					set x ":1000[format %02X $start]00"
					foreach y [lrange $::data $start [expr {($i*16)+15}]] {
						append x [format %02X $y]
					}
					append x [checksum $x]
					lappend res $x
				}
			}
		} else {
			lappend res $line
		}
	}

	return [join $res \n]
}

proc saveFile {raw} {
	if {[catch {open "backup_hex" w} f]} {
		tk_messageBox -message "Error: $f" -type error
	} else {
		puts -nonewline $f $raw
		close $f
	}
}

main
