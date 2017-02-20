/***************************************************************************
 * f9dasm -- Portable M6800/M6809/H6309/OS9/FLEX disassembler              *
 * HEAVILY modified by H.Seib to adapt it to his needs.                    *
 *                                                                         *
 * Line Disassembler Engine Copyright (C) 2000  Arto Salmi                 *
 * Various additions        Copyright (c) 2001-2009 Hermann Seib           *
 * Further additions        Copyright (c) 2014  Rainer Buchty              *
 *    - output nicing using separator after BRA/JMP/PULx PC/RTx/SWIx       *
 *    - label-overrun fix                                                  *
 *    - improved usage info for label-file parser                          *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program; if not, write to the Free Software             *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.               *
 ***************************************************************************/

typedef unsigned char  byte;

 struct
   {
   char *mne;
   byte bCodeJump;
   } mnemo[] =
   {
     { "???",   0 },                     /* _ill                              */
     { "ABA",   0 },                     /* _aba                              */
     { "ABX",   0 },                     /* _abx                              */
     { "ADCA",  0 },                     /* _adca                             */
     { "ADCB",  0 },                     /* _adcb                             */
     { "ADDA",  0 },                     /* _adda                             */
     { "ADDB",  0 },                     /* _addb                             */
     { "ADDD",  0 },                     /* _addd                             */
     { "ANDA",  0 },                     /* _anda                             */
     { "ANDB",  0 },                     /* _andb                             */
     { "ANDCC", 0 },                     /* _andcc                            */
     { "ASLA",  0 },                     /* _asla                             */
     { "ASLB",  0 },                     /* _aslb                             */
     { "ASL",   0 },                     /* _asl                              */
     { "ASRA",  0 },                     /* _asra                             */
     { "ASRB",  0 },                     /* _asrb                             */
     { "ASR",   0 },                     /* _asr                              */
     { "BCC",   1 },                     /* _bcc                              */
     { "LBCC",  1 },                     /* _lbcc                             */
     { "BCS",   1 },                     /* _bcs                              */
     { "LBCS",  1 },                     /* _lbcs                             */
     { "BEQ",   1 },                     /* _beq                              */
     { "LBEQ",  1 },                     /* _lbeq                             */
     { "BGE",   1 },                     /* _bge                              */
     { "LBGE",  1 },                     /* _lbge                             */
     { "BGT",   1 },                     /* _bgt                              */
     { "LBGT",  1 },                     /* _lbgt                             */
     { "BHI",   1 },                     /* _bhi                              */
     { "LBHI",  1 },                     /* _lbhi                             */
     { "BITA",  0 },                     /* _bita                             */
     { "BITB",  0 },                     /* _bitb                             */
     { "BLE",   1 },                     /* _ble                              */
     { "LBLE",  1 },                     /* _lble                             */
     { "BLS",   1 },                     /* _bls                              */
     { "LBLS",  1 },                     /* _lbls                             */
     { "BLT",   1 },                     /* _blt                              */
     { "LBLT",  1 },                     /* _lblt                             */
     { "BMI",   1 },                     /* _bmi                              */
     { "LBMI",  1 },                     /* _lbmi                             */
     { "BNE",   1 },                     /* _bne                              */
     { "LBNE",  1 },                     /* _lbne                             */
     { "BPL",   1 },                     /* _bpl                              */
     { "LBPL",  1 },                     /* _lbpl                             */
     { "BRA",   1 },                     /* _bra                              */
     { "LBRA",  1 },                     /* _lbra                             */
     { "BRN",   1 },                     /* _brn                              */
     { "LBRN",  1 },                     /* _lbrn                             */
     { "BSR",   1 },                     /* _bsr                              */
     { "LBSR",  1 },                     /* _lbsr                             */
     { "BVC",   1 },                     /* _bvc                              */
     { "LBVC",  1 },                     /* _lbvc                             */
     { "BVS",   1 },                     /* _bvs                              */
     { "LBVS",  1 },                     /* _lbvs                             */
     { "CBA",   0 },                     /* _cba                              */
     { "CLI",   0 },                     /* _cli                              */
     { "CLRA",  0 },                     /* _clra                             */
     { "CLRB",  0 },                     /* _clrb                             */
     { "CLR",   0 },                     /* _clr                              */
     { "CLC",   0 },                     /* _clc                              */
     { "CLV",   0 },                     /* _clv                              */
     { "CMPA",  0 },                     /* _cmpa                             */
     { "CMPB",  0 },                     /* _cmpb                             */
     { "CMPD",  0 },                     /* _cmpd                             */
     { "CMPS",  0 },                     /* _cmps                             */
     { "CMPU",  0 },                     /* _cmpu                             */
     { "CMPX",  0 },                     /* _cmpx                             */
     { "CMPY",  0 },                     /* _cmpy                             */
     { "COMA",  0 },                     /* _coma                             */
     { "COMB",  0 },                     /* _comb                             */
     { "COM",   0 },                     /* _com                              */
     { "CWAI",  0 },                     /* _cwai                             */
     { "DAA",   0 },                     /* _daa                              */
     { "DECA",  0 },                     /* _deca                             */
     { "DECB",  0 },                     /* _decb                             */
     { "DEC",   0 },                     /* _dec                              */
     { "DES",   0 },                     /* _des                              */
     { "DEX",   0 },                     /* _dex                              */
     { "EORA",  0 },                     /* _eora                             */
     { "EORB",  0 },                     /* _eorb                             */
     { "EXG",   0 },                     /* _exg                              */
     { "INCA",  0 },                     /* _inca                             */
     { "INCB",  0 },                     /* _incb                             */
     { "INC",   0 },                     /* _inc                              */
     { "INS",   0 },                     /* _ins                              */
     { "INX",   0 },                     /* _inx                              */
     { "JMP",   1 },                     /* _jmp                              */
     { "JSR",   1 },                     /* _jsr                              */
     { "LDA",   0 },                     /* _lda                              */
     { "LDB",   0 },                     /* _ldb                              */
     { "LDD",   0 },                     /* _ldd                              */
     { "LDS",   0 },                     /* _lds                              */
     { "LDU",   0 },                     /* _ldu                              */
     { "LDX",   0 },                     /* _ldx                              */
     { "LDY",   0 },                     /* _ldy                              */
     { "LEAS",  0 },                     /* _leas                             */
     { "LEAU",  0 },                     /* _leau                             */
     { "LEAX",  0 },                     /* _leax                             */
     { "LEAY",  0 },                     /* _leay                             */
     { "LSRA",  0 },                     /* _lsra                             */
     { "LSRB",  0 },                     /* _lsrb                             */
     { "LSR",   0 },                     /* _lsr                              */
     { "MUL",   0 },                     /* _mul                              */
     { "NEGA",  0 },                     /* _nega                             */
     { "NEGB",  0 },                     /* _negb                             */
     { "NEG",   0 },                     /* _neg                              */
     { "NOP",   0 },                     /* _nop                              */
     { "ORA",   0 },                     /* _ora                              */
     { "ORB",   0 },                     /* _orb                              */
     { "ORCC",  0 },                     /* _orcc                             */
     { "PSHA",  0 },                     /* _psha                             */
     { "PSHB",  0 },                     /* _pshb                             */
     { "PSHS",  0 },                     /* _pshs                             */
     { "PSHU",  0 },                     /* _pshu                             */
     { "PULA",  0 },                     /* _pula                             */
     { "PULB",  0 },                     /* _pulb                             */
     { "PULS",  0 },                     /* _puls                             */
     { "PULU",  0 },                     /* _pulu                             */
     { "ROLA",  0 },                     /* _rola                             */
     { "ROLB",  0 },                     /* _rolb                             */
     { "ROL",   0 },                     /* _rol                              */
     { "RORA",  0 },                     /* _rora                             */
     { "RORB",  0 },                     /* _rorb                             */
     { "ROR",   0 },                     /* _ror                              */
     { "RTI",   0 },                     /* _rti                              */
     { "RTS",   0 },                     /* _rts                              */
     { "SBA",   0 },                     /* _sba                              */
     { "SBCA",  0 },                     /* _sbca                             */
     { "SBCB",  0 },                     /* _sbcb                             */
     { "SEC",   0 },                     /* _sec                              */
     { "SEI",   0 },                     /* _sei                              */
     { "SEV",   0 },                     /* _sev                              */
     { "SEX",   0 },                     /* _sex                              */
     { "SEZ",   0 },                     /* _sez                              */
     { "STA",   0 },                     /* _sta                              */
     { "STB",   0 },                     /* _stb                              */
     { "STD",   0 },                     /* _std                              */
     { "STS",   0 },                     /* _sts                              */
     { "STU",   0 },                     /* _stu                              */
     { "STX",   0 },                     /* _stx                              */
     { "STY",   0 },                     /* _sty                              */
     { "SUBA",  0 },                     /* _suba                             */
     { "SUBB",  0 },                     /* _subb                             */
     { "SUBD",  0 },                     /* _subd                             */
     { "SWI",   0 },                     /* _swi                              */
     { "SWI2",  0 },                     /* _swi2                             */
     { "SWI3",  0 },                     /* _swi3                             */
     { "SYNC",  0 },                     /* _sync                             */
     { "TAB",   0 },                     /* _tab                              */
     { "TAP",   0 },                     /* _tap                              */
     { "TBA",   0 },                     /* _tba                              */
     { "TFR",   0 },                     /* _tfr                              */
     { "TPA",   0 },                     /* _tpa                              */
     { "TSTA",  0 },                     /* _tsta                             */
     { "TSTB",  0 },                     /* _tstb                             */
     { "TST",   0 },                     /* _tst                              */
     { "TSX",   0 },                     /* _tsx                              */
     { "TXS",   0 },                     /* _txs                              */
     { "WAI",   0 },                     /* _wai                              */
     { "RESET", 0 },                     /* _reset                            */
   /* 6800 EXTRA OPCODES */
     { "CPX",   0 },                     /* _cpx                              */
   /* 6309 EXTRA OPCODES */
     { "AIM",   0 },                     /* _aim                              */
     { "EIM",   0 },                     /* _eim                              */
     { "OIM",   0 },                     /* _oim                              */
     { "TIM",   0 },                     /* _tim                              */
     { "BAND",  0 },                     /* _band                             */
     { "BIAND", 0 },                     /* _biand                            */
     { "BOR",   0 },                     /* _bor                              */
     { "BIOR",  0 },                     /* _bior                             */
     { "BEOR",  0 },                     /* _beor                             */
     { "BIEOR", 0 },                     /* _bieor                            */
     { "LDBT",  0 },                     /* _ldbt                             */
     { "STBT",  0 },                     /* _stbt                             */
     { "TFM",   0 },                     /* _tfm                              */
     { "ADCD",  0 },                     /* _adcd                             */
     { "ADCR",  0 },                     /* _adcr                             */
     { "ADDE",  0 },                     /* _adde                             */
     { "ADDF",  0 },                     /* _addf                             */
     { "ADDW",  0 },                     /* _addw                             */
     { "ADDR",  0 },                     /* _addr                             */
     { "ANDD",  0 },                     /* _andd                             */
     { "ANDR",  0 },                     /* _andr                             */
     { "ASLD",  0 },                     /* _asld                             */
     { "ASRD",  0 },                     /* _asrd                             */
     { "BITD",  0 },                     /* _bitd                             */
     { "BITMD", 0 },                     /* _bitmd                            */
     { "CLRD",  0 },                     /* _clrd                             */
     { "CLRE",  0 },                     /* _clre                             */
     { "CLRF",  0 },                     /* _clrf                             */
     { "CLRW",  0 },                     /* _clrw                             */
     { "CMPE",  0 },                     /* _cmpe                             */
     { "CMPF",  0 },                     /* _cmpf                             */
     { "CMPW",  0 },                     /* _cmpw                             */
     { "CMPR",  0 },                     /* _cmpr                             */
     { "COMD",  0 },                     /* _comd                             */
     { "COME",  0 },                     /* _come                             */
     { "COMF",  0 },                     /* _comf                             */
     { "COMW",  0 },                     /* _comw                             */
     { "DECD",  0 },                     /* _dedc                             */
     { "DECE",  0 },                     /* _dece                             */
     { "DECF",  0 },                     /* _decf                             */
     { "DECW",  0 },                     /* _decw                             */
     { "DIVD",  0 },                     /* _divd                             */
     { "DIVQ",  0 },                     /* _divq                             */
     { "EORD",  0 },                     /* _eord                             */
     { "EORR",  0 },                     /* _eorr                             */
     { "INCD",  0 },                     /* _incd                             */
     { "INCE",  0 },                     /* _ince                             */
     { "INCF",  0 },                     /* _incf                             */
     { "INCW",  0 },                     /* _incw                             */
     { "LDE",   0 },                     /* _lde                              */
     { "LDF",   0 },                     /* _ldf                              */
     { "LDQ",   0 },                     /* _ldq                              */
     { "LDW",   0 },                     /* _ldw                              */
     { "LDMD",  0 },                     /* _ldmd                             */
     { "LSRD",  0 },                     /* _lsrd                             */
     { "LSRW",  0 },                     /* _lsrw                             */
     { "MULD",  0 },                     /* _muld                             */
     { "NEGD",  0 },                     /* _negd                             */
     { "ORD",   0 },                     /* _ord                              */
     { "ORR",   0 },                     /* _orr                              */
     { "PSHSW", 0 },                     /* _pshsw                            */
     { "PSHUW", 0 },                     /* _pshuw                            */
     { "PULSW", 0 },                     /* _pulsw                            */
     { "PULUW", 0 },                     /* _puluw                            */
     { "ROLD",  0 },                     /* _rold                             */
     { "ROLW",  0 },                     /* _rolw                             */
     { "RORD",  0 },                     /* _rord                             */
     { "RORW",  0 },                     /* _rorw                             */
     { "SBCD",  0 },                     /* _sbcd                             */
     { "SBCR",  0 },                     /* _sbcr                             */
     { "SEXW",  0 },                     /* _sexw                             */
     { "STE",   0 },                     /* _ste                              */
     { "STF",   0 },                     /* _stf                              */
     { "STQ",   0 },                     /* _stq                              */
     { "STW",   0 },                     /* _stw                              */
     { "SUBE",  0 },                     /* _sube                             */
     { "SUBF",  0 },                     /* _subf                             */
     { "SUBW",  0 },                     /* _subw                             */
     { "SUBR",  0 },                     /* _subr                             */
     { "TSTD",  0 },                     /* _tstd                             */
     { "TSTE",  0 },                     /* _tste                             */
     { "TSTF",  0 },                     /* _tstf                             */
     { "TSTW",  0 },                     /* _tstw                             */

   };
