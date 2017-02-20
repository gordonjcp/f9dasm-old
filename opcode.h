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

// opcode names and enums

#ifndef _OPCODE_H
#define _OPCODE_H

typedef unsigned char  byte;

extern struct
  {
  char *mne;
  byte bCodeJump;
} mnemo[];
enum addr_mode
   {
   _nom,     /* no mode                    */
   _imp,     /* inherent/implied           */
   _imb,     /* immediate byte             */
   _imw,     /* immediate word             */
   _dir,     /* direct                     */
   _ext,     /* extended                   */
   _ix8,     /* indexed for 6800           */
   _ind,     /* indexed                    */
   _reb,     /* relative byte              */
   _rew,     /* relative word              */
   _r1 ,     /* tfr/exg mode               */
   _r2 ,     /* pul/psh system             */
   _r3 ,     /* pul/psh user               */
   _bd ,     /* Bit Manipulation direct    */
   _bi ,     /* Bit Manipulation index     */
   _be ,     /* Bit Manipulation extended  */
   _bt ,     /* Bit Transfers direct       */
   _t1 ,     /* Block Transfer r0+,r1+     */
   _t2 ,     /* Block Transfer r0-,r1-     */
   _t3 ,     /* Block Transfer r0+,r1      */
   _t4 ,     /* Block Transfer r0,r1+      */
   _iml,     /* immediate 32-bit           */
   _dom,    /* direct bit manipulation */
   };

 enum opcodes
   {
   _ill=0,
   _aba,  _abx,  _adca, _adcb, _adda, _addb, _addd, _anda, _andb,
   _andcc,_asla, _aslb, _asl,  _asra, _asrb, _asr,  _bcc,  _lbcc,
   _bcs,  _lbcs, _beq,  _lbeq, _bge,  _lbge, _bgt,  _lbgt, _bhi,
   _lbhi, _bita, _bitb, _ble,  _lble, _bls,  _lbls, _blt,  _lblt,
   _bmi,  _lbmi, _bne,  _lbne, _bpl,  _lbpl, _bra,  _lbra, _brn,
   _lbrn, _bsr,  _lbsr, _bvc,  _lbvc, _bvs,  _lbvs,
   _cba,  _cli,  _clra, _clrb, _clr,  _clc,  _clv,
   _cmpa, _cmpb, _cmpd, _cmps, _cmpu, _cmpx, _cmpy, _coma,
   _comb, _com,  _cwai, _daa,  _deca, _decb, _dec,  _des,  _dex,
   _eora, _eorb,
   _exg,  _inca, _incb, _inc,  _ins,  _inx,
   _jmp,  _jsr,  _lda,  _ldb,  _ldd,
   _lds,  _ldu,  _ldx,  _ldy,  _leas, _leau, _leax, _leay, _lsra,
   _lsrb, _lsr,  _mul,  _nega, _negb, _neg,  _nop,  _ora,  _orb,
   _orcc, _psha, _pshb, _pshs, _pshu,
   _pula, _pulb, _puls, _pulu, _rola, _rolb, _rol,  _rora,
   _rorb, _ror,  _rti,  _rts,  _sba,  _sbca, _sbcb,
   _sec,  _sei,  _sev,  _sex,  _sez,  _sta,
   _stb,  _std,  _sts,  _stu,  _stx,  _sty,  _suba, _subb, _subd,
   _swi,  _swi2, _swi3, _sync, _tab,  _tap,  _tba,
   _tfr,  _tpa,  _tsta, _tstb,
   _tst,  _tsx,  _txs,
   _wai,  _reset,
   /* 6800 extra opcodes */
   _cpx,
   /* 6309 extra opcodes */
   _aim,  _eim,  _oim,  _tim,  _band, _biand,_bor,  _bior, _beor,
   _bieor,_ldbt, _stbt, _tfm,  _adcd, _adcr, _adde, _addf, _addw,
   _addr, _andd, _andr, _asld, _asrd, _bitd, _bitmd,_clrd, _clre,
   _clrf, _clrw, _cmpe, _cmpf, _cmpw, _cmpr, _comd, _come, _comf,
   _comw, _decd, _dece, _decf, _decw, _divd, _divq, _eord, _eorr,
   _incd, _ince, _incf, _incw, _lde,  _ldf,  _ldq,  _ldw,  _ldmd,
   _lsrd, _lsrw, _muld, _negd, _ord,  _orr,  _pshsw,_pshuw,_pulsw,
   _puluw,_rold, _rolw, _rord, _rorw, _sbcd, _sbcr, _sexw, _ste,
   _stf,  _stq,  _stw,  _sube, _subf, _subw, _subr, _tstd, _tste,
   _tstf, _tstw,
   /* 68hc11 extra opcodes */
   _pulx, _pshx, _bset, _bclr, _brset, _brclr,

   };


#endif
