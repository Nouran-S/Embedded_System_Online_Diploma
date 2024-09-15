/* 
	Start UP contrex-M3
	ENG. Nouran
*/

.section .vectors
.word 0x20001000		/* Stack Top Address */
.word _reset			/* 1 Reset */
.word _vextor_handler   /* 2 NMI */
.word _vextor_handler	/* 3 Hard Fault */
.word _vextor_handler	/* 4 ... */

.section .text
_reset:
	bl main
	b  .

.thumb_func
_vextor_handler:
	b _reset
