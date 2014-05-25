/*--------------------------------------------------------------------------
REG320.H

Header file for DS80C320/DS80C323.
Copyright (c) 1988-2002 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.
--------------------------------------------------------------------------*/

/*  BYTE Registers  */
sfr P0     = 0x80;
sfr P1     = 0x90;
sfr P2     = 0xA0;
sfr P3     = 0xB0;
sfr PSW    = 0xD0;
sfr ACC    = 0xE0;
sfr B      = 0xF0;
sfr SP     = 0x81;
sfr DPL    = 0x82;
sfr DPH    = 0x83;
sfr PCON   = 0x87;
sfr TCON   = 0x88;
sfr TMOD   = 0x89;
sfr TL0    = 0x8A;
sfr TL1    = 0x8B;
sfr TH0    = 0x8C;
sfr TH1    = 0x8D;

sfr IE_1   = 0xA7; //tx3701

sfr IE     = 0xA8;
sfr INTE   = 0xA9; //tx3706

sfr IP     = 0xB8;
sfr SCON0  = 0x98;
sfr SBUF0  = 0x99;

/*  DS80C320 Extensions  */
sfr DPL1   = 0x84;
sfr DPH1   = 0x85;
sfr DPS    = 0x86;
sfr CKCON  = 0x8E;
sfr EXIF   = 0x91;
sfr P0PUN  = 0x92;
sfr SADDR0 = 0xA9;
sfr SADDR1 = 0xAA;
sfr SADEN0 = 0xB9;
sfr SADEN1 = 0xBA;
sfr SCON1  = 0xC0;
sfr SBUF1  = 0xC1;
sfr STATUS = 0xC5;
sfr TA     = 0xC7;
sfr T2CON  = 0xC8;
sfr T2MOD  = 0xC9;
sfr RCAP2L = 0xCA;
sfr RCAP2H = 0xCB;
sfr TL2    = 0xCC;
sfr TH2    = 0xCD;
sfr WDCON  = 0xD8;
sfr EIE    = 0xE8;
sfr EIP    = 0xF8;

/*  BIT Registers  */
/*  PSW */
sbit CY    = PSW^7;
sbit AC    = PSW^6;
sbit F0    = PSW^5;
sbit RS1   = PSW^4;
sbit RS0   = PSW^3;
sbit OV    = PSW^2;
sbit FL    = PSW^1;
sbit P     = PSW^0;

/*  TCON  */
sbit TF1   = TCON^7;
sbit TR1   = TCON^6;
sbit TF0   = TCON^5;
sbit TR0   = TCON^4;
sbit IE1   = TCON^3;
sbit IT1   = TCON^2;
sbit IE0   = TCON^1;
sbit IT0   = TCON^0;

/*  IE  */
sbit EA    = IE^7;
sbit ES1   = IE^6;
sbit ET2   = IE^5;
sbit ES0   = IE^4;
sbit ET1   = IE^3;
sbit EX1   = IE^2;
sbit ET0   = IE^1;
sbit EX0   = IE^0;

/*  IP  */
sbit PS1   = IP^6;
sbit PT2   = IP^5;
sbit PS0   = IP^4;
sbit PT1   = IP^3;
sbit PX1   = IP^2;
sbit PT0   = IP^1;
sbit PX0   = IP^0;

/*  SCON0  */
sbit SM0   = SCON0^7; /* alternative SM0_FE_0 */
sbit SM1   = SCON0^6; /* alternative SM1_0 */
sbit SM2   = SCON0^5; /* alternative SM2_0 */
sbit REN   = SCON0^4; /* alternative REN_0 */
sbit TB8   = SCON0^3; /* alternative TB8_0 */
sbit RB8   = SCON0^2; /* alternative RB8_0 */
sbit TI    = SCON0^1; /* alternative TI_0  */
sbit RI    = SCON0^0; /* alternative RI_0  */

/*  SCON1  */
sbit SM01  = SCON1^7; /* alternative SM0_FE_1  */
sbit SM11  = SCON1^6; /* alternative SM1_1  */
sbit SM21  = SCON1^5; /* alternative SM2_1  */
sbit REN1  = SCON1^4; /* alternative REN_1  */
sbit TB81  = SCON1^3; /* alternative TB8_1  */
sbit RB81  = SCON1^2; /* alternative RB8_1  */
sbit TI1   = SCON1^1; /* alternative TI_1   */
sbit RI1   = SCON1^0; /* alternative RI_1   */

/*  T2CON  */
sbit TF2    = T2CON^7;
sbit EXF2   = T2CON^6;
sbit RCLK   = T2CON^5;
sbit TCLK   = T2CON^4;
sbit EXEN2  = T2CON^3;
sbit TR2    = T2CON^2;
sbit C_T2   = T2CON^1;
sbit CP_RL2 = T2CON^0;

/*  WDCON  */
sbit SMOD_1 = WDCON^7;
sbit POR    = WDCON^6;
sbit EPFI   = WDCON^5;
sbit PFI    = WDCON^4;
sbit WDIF   = WDCON^3;
sbit WTRF   = WDCON^2;
sbit EWT    = WDCON^1;
sbit RWT    = WDCON^0;

/*  EIE  */
sbit EWDI  = EIE^4;
sbit EX5   = EIE^3;
sbit EX4   = EIE^2;
sbit EX3   = EIE^1;
sbit EX2   = EIE^0;

/*  EIP  */
sbit PWDI  = EIP^4;
sbit PX5   = EIP^3;
sbit PX4   = EIP^2;
sbit PX3   = EIP^1;
sbit PX2   = EIP^0;

/*LCM*/
sbit RS_LCM	= P3^5;
sbit RW_LCM	= P3^6;
sbit EN_LCM	= P3^7;

/*  tx3702  */

sfr p0oe   = 0x91;
sfr p4mode = 0x92;
sfr p2oe   = 0x93;
sfr option = 0x94;
sfr INTFLG = 0x95;

sfr p1inte 	 = 0x96;
sfr swcmd 	 = 0x97;
sfr pwm0prd  = 0x9a;
sfr pwm0duty = 0x9b;
sfr pwm1prd  = 0x9c;
sfr pwm1duty = 0x9d;
sfr pwmcon 	 = 0xa1;


sfr P1MODL = 0xa2;
sfr P1MODH = 0xa3;
sfr P3MODL = 0xa4;
sfr P3MODH = 0xa5;
sfr PINMOD = 0xa6;

sfr INTE1  = 0xa9;

sfr ADTKDT = 0xaa;
sfr ADCDH  = 0xab;
sfr TKDL   = 0xac;
sfr TKCON  = 0xad;
sfr CHSEL  = 0xae;

sfr lcdcon	   = 0xb1;
sfr lcdcon2	   = 0xb2;
sfr lcdpin	   = 0xb3;
sfr iph	   	   = 0xb9;

sfr IP1	   = 0xba;
sfr IP1H   = 0xbb;
sfr SPCON  = 0xbc;
sfr SPSTA  = 0xbd;
sfr SPDAT  = 0xbe;

sfr p5		= 0xc0;
//sfr t2con	= 0xc8;
sfr rcp2l	= 0xca;
sfr rcp2h	= 0xcb;
//sfr tl2		= 0xcc;
//sfr th2		= 0xcd;

sfr CLKCON = 0xd8;


sfr	p4	   = 0xe8;
sfr	cfgl   = 0xf7;
sfr AUX1   = 0xf8;

sfr icecon   = 0xf9;
sfr rtcode   = 0xfa;
sfr icercd   = 0xfb;
sfr icecmdl  = 0xfc;
sfr icecmdh  = 0xfd;
sfr icetxd   = 0xfe;



#define BIT0 	0x01
#define BIT1 	0x02
#define BIT2 	0x04
#define BIT3 	0x08
#define BIT4 	0x10
#define BIT5 	0x20
#define BIT6 	0x40
#define BIT7 	0x80


