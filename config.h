/* Fuse configuration for PIC16F690 */

__CONFIG(
	HS &           // use high speed crystal 
	UNPROTECT &    // disable code protect
	WDTDIS &       // disable watchdog timer
	PWRTEN &       // enable powerup timer
	MCLRDIS &      // disable MCLR
	FCMDIS         // disable failsafe clock monitor
);
