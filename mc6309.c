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

// opcodes for 6309

#include "opcode.h"

byte h6309_codes[512] =
  {
  _neg  ,_dir,   _oim  ,_bd ,   _aim  ,_bd ,   _com  ,_dir,     /* 00..03 */
  _lsr  ,_dir,   _eim  ,_bd ,   _ror  ,_dir,   _asr  ,_dir,     /* 04..07 */
  _asl  ,_dir,   _rol  ,_dir,   _dec  ,_dir,   _tim  ,_bd ,     /* 08..0B */
  _inc  ,_dir,   _tst  ,_dir,   _jmp  ,_dir,   _clr  ,_dir,     /* 0C..0F */
  _ill  ,_nom,   _ill  ,_nom,   _nop  ,_imp,   _sync ,_imp,     /* 10..13 */
  _sexw ,_imp,   _ill  ,_nom,   _lbra ,_rew,   _lbsr ,_rew,     /* 14..17 */
  _ill  ,_nom,   _daa  ,_imp,   _orcc ,_imb,   _ill  ,_nom,     /* 18..1B */
  _andcc,_imb,   _sex  ,_imp,   _exg  ,_r1 ,   _tfr  ,_r1 ,     /* 1C..1F */
  _bra  ,_reb,   _brn  ,_reb,   _bhi  ,_reb,   _bls  ,_reb,     /* 20..23 */
  _bcc  ,_reb,   _bcs  ,_reb,   _bne  ,_reb,   _beq  ,_reb,     /* 24..27 */
  _bvc  ,_reb,   _bvs  ,_reb,   _bpl  ,_reb,   _bmi  ,_reb,     /* 28..2B */
  _bge  ,_reb,   _blt  ,_reb,   _bgt  ,_reb,   _ble  ,_reb,     /* 2C..2F */
  _leax ,_ind,   _leay ,_ind,   _leas ,_ind,   _leau ,_ind,     /* 30..33 */
  _pshs ,_r2 ,   _puls ,_r2 ,   _pshu ,_r3 ,   _pulu ,_r3 ,     /* 34..37 */
  _ill  ,_nom,   _rts  ,_imp,   _abx  ,_imp,   _rti  ,_imp,     /* 38..3B */
  _cwai ,_imb,   _mul  ,_imp,   _reset,_imp,   _swi  ,_imp,     /* 3C..3F */
  _nega ,_imp,   _ill  ,_nom,   _ill  ,_nom,   _coma ,_imp,     /* 40..43 */
  _lsra ,_imp,   _ill  ,_nom,   _rora ,_imp,   _asra ,_imp,     /* 44..47 */
  _asla ,_imp,   _rola ,_imp,   _deca ,_imp,   _ill  ,_nom,     /* 48..4B */
  _inca ,_imp,   _tsta ,_imp,   _ill  ,_nom,   _clra ,_imp,     /* 4C..4F */
  _negb ,_imp,   _ill  ,_nom,   _ill  ,_nom,   _comb ,_imp,     /* 50..53 */
  _lsrb ,_imp,   _ill  ,_nom,   _rorb ,_imp,   _asrb ,_imp,     /* 54..57 */
  _aslb ,_imp,   _rolb ,_imp,   _decb ,_imp,   _ill  ,_nom,     /* 58..5B */
  _incb ,_imp,   _tstb ,_imp,   _ill  ,_nom,   _clrb ,_imp,     /* 5C..5F */
  _neg  ,_ind,   _oim  ,_bi ,   _aim  ,_bi ,   _com  ,_ind,     /* 60..63 */
  _lsr  ,_ind,   _eim  ,_bi ,   _ror  ,_ind,   _asr  ,_ind,     /* 64..67 */
  _asl  ,_ind,   _rol  ,_ind,   _dec  ,_ind,   _tim  ,_bi ,     /* 68..6B */
  _inc  ,_ind,   _tst  ,_ind,   _jmp  ,_ind,   _clr  ,_ind,     /* 6C..6F */
  _neg  ,_ext,   _oim  ,_be ,   _aim  ,_be ,   _com  ,_ext,     /* 70..73 */
  _lsr  ,_ext,   _eim  ,_be ,   _ror  ,_ext,   _asr  ,_ext,     /* 74..77 */
  _asl  ,_ext,   _rol  ,_ext,   _dec  ,_ext,   _tim  ,_be ,     /* 78..7B */
  _inc  ,_ext,   _tst  ,_ext,   _jmp  ,_ext,   _clr  ,_ext,     /* 7C..7F */
  _suba ,_imb,   _cmpa ,_imb,   _sbca ,_imb,   _subd ,_imw,     /* 80..83 */
  _anda ,_imb,   _bita ,_imb,   _lda  ,_imb,   _ill  ,_nom,     /* 84..87 */
  _eora ,_imb,   _adca ,_imb,   _ora  ,_imb,   _adda ,_imb,     /* 88..8B */
  _cmpx ,_imw,   _bsr  ,_reb,   _ldx  ,_imw,   _ill  ,_nom,     /* 8C..8F */
  _suba ,_dir,   _cmpa ,_dir,   _sbca ,_dir,   _subd ,_dir,     /* 90..93 */
  _anda ,_dir,   _bita ,_dir,   _lda  ,_dir,   _sta  ,_dir,     /* 94..97 */
  _eora ,_dir,   _adca ,_dir,   _ora  ,_dir,   _adda ,_dir,     /* 98..9B */
  _cmpx ,_dir,   _jsr  ,_dir,   _ldx  ,_dir,   _stx  ,_dir,     /* 9C..9F */
  _suba ,_ind,   _cmpa ,_ind,   _sbca ,_ind,   _subd ,_ind,     /* A0..A3 */
  _anda ,_ind,   _bita ,_ind,   _lda  ,_ind,   _sta  ,_ind,     /* A4..A7 */
  _eora ,_ind,   _adca ,_ind,   _ora  ,_ind,   _adda ,_ind,     /* A8..AB */
  _cmpx ,_ind,   _jsr  ,_ind,   _ldx  ,_ind,   _stx  ,_ind,     /* AC..AF */
  _suba ,_ext,   _cmpa ,_ext,   _sbca ,_ext,   _subd ,_ext,     /* B0..B3 */
  _anda ,_ext,   _bita ,_ext,   _lda  ,_ext,   _sta  ,_ext,     /* B4..B7 */
  _eora ,_ext,   _adca ,_ext,   _ora  ,_ext,   _adda ,_ext,     /* B8..BB */
  _cmpx ,_ext,   _jsr  ,_ext,   _ldx  ,_ext,   _stx  ,_ext,     /* BC..BF */
  _subb ,_imb,   _cmpb ,_imb,   _sbcb ,_imb,   _addd ,_imw,     /* C0..C3 */
  _andb ,_imb,   _bitb ,_imb,   _ldb  ,_imb,   _ill  ,_nom,     /* C4..C7 */
  _eorb ,_imb,   _adcb ,_imb,   _orb  ,_imb,   _addb ,_imb,     /* C8..CB */
  _ldd  ,_imw,   _ldq  ,_iml,   _ldu  ,_imw,   _ill  ,_nom,     /* CC..CF */
  _subb ,_dir,   _cmpb ,_dir,   _sbcb ,_dir,   _addd ,_dir,     /* D0..D3 */
  _andb ,_dir,   _bitb ,_dir,   _ldb  ,_dir,   _stb  ,_dir,     /* D4..D7 */
  _eorb ,_dir,   _adcb ,_dir,   _orb  ,_dir,   _addb ,_dir,     /* D8..DB */
  _ldd  ,_dir,   _std  ,_dir,   _ldu  ,_dir,   _stu  ,_dir,     /* DC..DF */
  _subb ,_ind,   _cmpb ,_ind,   _sbcb ,_ind,   _addd ,_ind,     /* E0..E3 */
  _andb ,_ind,   _bitb ,_ind,   _ldb  ,_ind,   _stb  ,_ind,     /* E4..E7 */
  _eorb ,_ind,   _adcb ,_ind,   _orb  ,_ind,   _addb ,_ind,     /* E8..EB */
  _ldd  ,_ind,   _std  ,_ind,   _ldu  ,_ind,   _stu  ,_ind,     /* EC..EF */
  _subb ,_ext,   _cmpb ,_ext,   _sbcb ,_ext,   _addd ,_ext,     /* F0..F3 */
  _andb ,_ext,   _bitb ,_ext,   _ldb  ,_ext,   _stb  ,_ext,     /* F4..F7 */
  _eorb ,_ext,   _adcb ,_ext,   _orb  ,_ext,   _addb ,_ext,     /* F8..FB */
  _ldd  ,_ext,   _std  ,_ext,   _ldu  ,_ext,   _stu  ,_ext,     /* FC..FF */
  };

byte h6309_codes10[512] =
  {
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 00..03 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 04..07 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 08..0B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 0C..0F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 10..13 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 14..17 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 18..1B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 1C..1F */
  _ill  ,_nom,   _lbrn ,_rew,   _lbhi ,_rew,   _lbls ,_rew,     /* 20..23 */
  _lbcc ,_rew,   _lbcs ,_rew,   _lbne ,_rew,   _lbeq ,_rew,     /* 24..27 */
  _lbvc ,_rew,   _lbvs ,_rew,   _lbpl ,_rew,   _lbmi ,_rew,     /* 28..2B */
  _lbge ,_rew,   _lblt ,_rew,   _lbgt ,_rew,   _lble ,_rew,     /* 2C..2F */
  _addr ,_r1 ,   _adcr ,_r1 ,   _subr ,_r1 ,   _sbcr ,_r1 ,     /* 30..33 */
  _andr ,_r1 ,   _orr  ,_r1 ,   _eorr ,_r1 ,   _cmpr ,_r1 ,     /* 34..37 */
  _pshsw,_imp,   _pulsw,_imp,   _pshuw,_imp,   _puluw,_imp,     /* 38..3B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _swi2 ,_imp,     /* 3C..3F */
  _negd ,_imp,   _ill  ,_nom,   _ill  ,_nom,   _comd ,_imp,     /* 40..43 */
  _lsrd ,_imp,   _ill  ,_nom,   _rord ,_imp,   _asrd ,_imp,     /* 44..47 */
  _asld ,_imp,   _rold ,_imp,   _decd ,_imp,   _ill  ,_nom,     /* 48..4B */
  _incd ,_imp,   _tstd ,_imp,   _ill  ,_nom,   _clrd ,_imp,     /* 4C..4F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _comw ,_imp,     /* 50..53 */
  _lsrw ,_imp,   _ill  ,_nom,   _rorw ,_imp,   _ill  ,_nom,     /* 54..57 */
  _ill  ,_nom,   _rolw ,_imp,   _decw ,_imp,   _ill  ,_nom,     /* 58..5B */
  _incw ,_imp,   _tstw ,_imp,   _ill  ,_nom,   _clrw ,_imp,     /* 5C..5F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 60..63 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 64..67 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 68..6B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 6C..6F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 70..73 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 74..77 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 78..7B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 7C..7F */
  _subw ,_imw,   _cmpw ,_imw,   _sbcd ,_imw,   _cmpd ,_imw,     /* 80..83 */
  _andd ,_imw,   _bitd ,_imw,   _ldw  ,_imw,   _ill  ,_nom,     /* 84..87 */
  _eord ,_imw,   _adcd ,_imw,   _ord  ,_imw,   _addw ,_imw,     /* 88..8B */
  _cmpy ,_imw,   _ill  ,_nom,   _ldy  ,_imw,   _ill  ,_nom,     /* 8C..8F */
  _subw ,_dir,   _cmpw ,_dir,   _sbcd ,_dir,   _cmpd ,_dir,     /* 90..93 */
  _andd ,_dir,   _bitd ,_dir,   _ldw  ,_dir,   _stw  ,_dir,     /* 94..97 */
  _eord ,_dir,   _adcd ,_dir,   _ord  ,_dir,   _addw ,_dir,     /* 98..9B */
  _cmpy ,_dir,   _ill  ,_nom,   _ldy  ,_dir,   _sty  ,_dir,     /* 9C..9F */
  _subw ,_ind,   _cmpw ,_ind,   _sbcd ,_ind,   _cmpd ,_ind,     /* A0..A3 */
  _andd ,_ind,   _bitd ,_ind,   _ldw  ,_ind,   _stw  ,_ind,     /* A4..A7 */
  _eord ,_ind,   _adcd ,_ind,   _ord  ,_ind,   _addw ,_ind,     /* A8..AB */
  _cmpy ,_ind,   _ill  ,_nom,   _ldy  ,_ind,   _sty  ,_ind,     /* AC..AF */
  _subw ,_ext,   _cmpw ,_ext,   _sbcd ,_ext,   _cmpd ,_ext,     /* B0..B3 */
  _andd ,_ext,   _bitd ,_ext,   _ldw  ,_ext,   _stw  ,_ext,     /* B4..B7 */
  _eord ,_ext,   _adcd ,_ext,   _ord  ,_ext,   _addw ,_ext,     /* B8..BB */
  _cmpy ,_ext,   _ill  ,_nom,   _ldy  ,_ext,   _sty  ,_ext,     /* BC..BF */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* C0..C3 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* C4..C7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* C8..CB */
  _ill  ,_nom,   _ill  ,_nom,   _lds  ,_imw,   _ill  ,_nom,     /* CC..CF */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* D0..D3 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* D4..D7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* D8..DB */
  _ldq  ,_dir,   _stq  ,_dir,   _lds  ,_dir,   _sts  ,_dir,     /* DC..DF */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* E0..E3 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* E4..E7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* E8..EB */
  _ldq  ,_ind,   _stq  ,_ind,   _lds  ,_ind,   _sts  ,_ind,     /* EC..EF */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* F0..F3 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* F4..F7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* F8..FB */
  _ldq  ,_ext,   _stq  ,_ext,   _lds  ,_ext,   _sts  ,_ext,     /* FC..FF */
  };

byte h6309_codes11[512] =
  {
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 00..03 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 04..07 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 08..0B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 0C..0F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 10..13 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 14..17 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 18..1B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 1C..1F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 20..23 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 24..27 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 28..2B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 2C..2F */
  _band ,_bt ,   _biand,_bt ,   _bor  ,_bt ,   _bior ,_bt ,     /* 30..33 */
  _beor ,_bt ,   _bieor,_bt ,   _ldbt ,_bt ,   _stbt ,_bt ,     /* 34..37 */
  _tfm  ,_t1 ,   _tfm  ,_t2 ,   _tfm  ,_t3 ,   _tfm  ,_t4 ,     /* 38..3B */
  _bitmd,_imb,   _ldmd ,_imb,   _ill  ,_nom,   _swi3 ,_imp,     /* 3C..3F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _come ,_imp,     /* 40..43 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 44..47 */
  _ill  ,_nom,   _ill  ,_nom,   _dece ,_imp,   _ill  ,_nom,     /* 48..4B */
  _ince ,_imp,   _tste ,_imp,   _ill  ,_nom,   _clre ,_imp,     /* 4C..4F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _comf ,_imp,     /* 50..53 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 54..57 */
  _ill  ,_nom,   _ill  ,_nom,   _decf ,_imp,   _ill  ,_nom,     /* 58..5B */
  _incf ,_imp,   _tstf ,_imp,   _ill  ,_nom,   _clrf ,_imp,     /* 5C..5F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 60..63 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 64..67 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 68..6B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 6C..6F */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 70..73 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 74..77 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 78..7B */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* 7C..7F */
  _sube ,_imb,   _cmpe ,_imb,   _ill  ,_nom,   _cmpu ,_imw,     /* 80..83 */
  _ill  ,_nom,   _ill  ,_nom,   _lde  ,_imb,   _ill  ,_nom,     /* 84..87 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _adde ,_imb,     /* 88..8B */
  _cmps ,_imw,   _divd ,_imb,   _divq ,_imw,   _muld ,_imw,     /* 8C..8F */
  _sube ,_dir,   _cmpe ,_dir,   _ill  ,_nom,   _cmpu ,_dir,     /* 90..93 */
  _ill  ,_nom,   _ill  ,_nom,   _lde  ,_dir,   _ste  ,_dir,     /* 94..97 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _adde ,_dir,     /* 98..9B */
  _cmps ,_dir,   _divd ,_dir,   _divq ,_dir,   _muld ,_dir,     /* 9C..9F */
  _sube ,_ind,   _cmpe ,_ind,   _ill  ,_nom,   _cmpu ,_ind,     /* A0..A3 */
  _ill  ,_nom,   _ill  ,_nom,   _lde  ,_ind,   _ste  ,_ind,     /* A4..A7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _adde ,_ind,     /* A8..AB */
  _cmps ,_ind,   _divd ,_ind,   _divq ,_ind,   _muld ,_ind,     /* AC..AF */
  _sube ,_ext,   _cmpe ,_ext,   _ill  ,_nom,   _cmpu ,_ext,     /* B0..B3 */
  _ill  ,_nom,   _ill  ,_nom,   _lde  ,_ext,   _ste  ,_ext,     /* B4..B7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _adde ,_ext,     /* B8..BB */
  _cmps ,_ext,   _divd ,_ext,   _divq ,_ext,   _muld ,_ext,     /* BC..BF */
  _subf ,_imb,   _cmpf ,_imb,   _ill  ,_nom,   _ill  ,_nom,     /* C0..C3 */
  _ill  ,_nom,   _ill  ,_nom,   _ldf  ,_imb,   _ill  ,_nom,     /* C4..C7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _addf ,_imb,     /* C8..CB */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* CC..CF */
  _subf ,_dir,   _cmpf ,_dir,   _ill  ,_nom,   _ill  ,_nom,     /* D0..D3 */
  _ill  ,_nom,   _ill  ,_nom,   _ldf  ,_dir,   _stf  ,_dir,     /* D4..D7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _addf ,_dir,     /* D8..DB */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* DC..DF */
  _subf ,_ind,   _cmpf ,_ind,   _ill  ,_nom,   _ill  ,_nom,     /* E0..E3 */
  _ill  ,_nom,   _ill  ,_nom,   _ldf  ,_ind,   _stf  ,_ind,     /* E4..E7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _addf ,_ind,     /* E8..EB */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* EC..EF */
  _subf ,_ext,   _cmpf ,_ext,   _ill  ,_nom,   _ill  ,_nom,     /* F0..F3 */
  _ill  ,_nom,   _ill  ,_nom,   _ldf  ,_ext,   _stf  ,_ext,     /* F4..F7 */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _addf ,_ext,     /* F8..FB */
  _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,   _ill  ,_nom,     /* FC..FF */
  };

char *h6309_exg_tfr[] =
  {
    "D", "X", "Y", "U", "S", "PC","W" ,"V",
    "A", "B", "CC","DP","0", "0", "E", "F"
  };
