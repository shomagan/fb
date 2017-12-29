/* ФБ "Вычислитель Кнап" */
#include "../vars.h"
#include "../kernel.h"
#include "../regs.h"

#include "fb00064.h"

///#define FB64_DEBUG

void fb00064_exec(void) {
/*	fb00064_IN_type *IN = (fb00064_IN_type *) FBInputs;
	fb00064_VAR_type *VAR = (fb00064_VAR_type *) FBVars;
	fb00064_OUT_type *OUT = (fb00064_OUT_type *) FBOutputs;
  
  // Локальные переменные
  static unsigned short int LenLo, LenHi;
  static unsigned char i, j, iidx1, LENGTH2;
  static short total_area;
  
  static float c1_1, c1_2, c1_1_1, c1_2_1, c1_1_2, c1_2_2;
  static float c2_1, c2_2, c2_3, c2_1_1, c2_1_2, c2_1_3;
  static float c3_1, c3_2, c3_3, c3_4;
  static float par_L1, par_L2;
  
  static short a1, a2;
  static short hBScope, lBScope, Scope_of_dnm;
  static unsigned char P4_1_idx, P4_2_idx, P4_3_idx;
  
  static float b1, b2, b3, b4;
  static float w1, w2;
  
  OUT->KnapOK.Data.bit = 0;
  
  switch (OUT->Stage.Data.uint8)
  {
  case 0:
    //-------------- Подготовка исполняется 0.3 мс -----------------------------
    if (IN->Start.Data.bit)
    {
#ifdef FB64_DEBUG
      DBGU_fprint("New DNM[%d]\r\n", IN->LenDNM_in.Data.uint16);
#endif
      
      if ( (IN->LenDNM_in.Data.uint16) && (IN->LenDNM_in.Data.uint16 <= MaxLenDNM) )  // Размер массива ДНМ не больше максимального
      {
        VAR->LenDNM.Data.uint16 = IN->LenDNM_in.Data.uint16;
#ifdef FB64_DEBUG
        DBGU_fprint("LenDNM=%d, [%d,%d,..,%d,%d]\r\n", VAR->LenDNM.Data.uint16, IN->DNM_in[0].Data.uint8, IN->DNM_in[1].Data.uint8, IN->DNM_in[VAR->LenDNM.Data.uint16-2].Data.uint8, IN->DNM_in[VAR->LenDNM.Data.uint16-1].Data.uint8);
#endif
        for (i=0; i < VAR->LenDNM.Data.uint16; i++)
          VAR->BufCor[i+1].Data.uint8 = IN->DNM_in[i].Data.uint8;         
      }
      else
        VAR->LenDNM.Data.uint16 = 0;
      
      if (VAR->LenDNM.Data.uint16)
      {
        LENGTH2 = VAR->LenDNM.Data.uint16 >> 1;
        
        //Коррекция массива
        for (j=0; j < nF; j++)
          VAR->aFourier[j].Data.float32 = VAR->bFourier[j].Data.float32 = 0;
        
        VAR->omega.Data.float32 = (2 * 3.14159265358979) / (2*LENGTH2-1);
        OUT->Stage.Data.uint8++;
      }
    }
    //--------------------------------------------------------------------------
    break;
  case 1:       // Стадии работы 
  case 2:       // первого "тяжёлого" цикла
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 8:
  case 9:
  case 10:
    switch (OUT->Stage.Data.uint8)
    {
    case 1:
      LenLo = 2;
      LenHi = 20;
      break;
    case 2:
      LenLo = 20;
      LenHi = 40;
      break;
    case 3:
      LenLo = 40;
      LenHi = 60;
      break;
    case 4:
      LenLo = 60;
      LenHi = 80;
      break;
    case 5:
      LenLo = 80;
      LenHi = 100;
      break;
    case 6:
      LenLo = 100;
      LenHi = 120;
      break;
    case 7:
      LenLo = 120;
      LenHi = 140;
      break;
    case 8:
      LenLo = 140;
      
      if (VAR->LenDNM.Data.uint16 > 160)
        LenHi = 160;
      else
      {
        LenHi = VAR->LenDNM.Data.uint16+1;
        OUT->Stage.Data.uint8 = 10; 
      }
      break;
    case 9:
      LenLo = 160;
      if (VAR->LenDNM.Data.uint16 > 180)
        LenHi = 180;
      else
      {
        LenHi = VAR->LenDNM.Data.uint16+1;
        OUT->Stage.Data.uint8 = 10; 
      }
      break;
    case 10:
      LenLo = 180;
      LenHi = VAR->LenDNM.Data.uint16+1;
      OUT->Stage.Data.uint8 = 10; 
      break;
    }

#ifdef FB64_DEBUG
      DBGU_fprint("CYC1[%d,%d]\r\n", LenLo, LenHi-1);
#endif
    
    ///------- Цикл обрабатывается 93 мс -----------------------------------------
    for (i=LenLo; i < LenHi; i++)
    {
      VAR->da2.Data.float32 = VAR->BufCor[i].Data.uint8;
      VAR->x.Data.float32 = VAR->omega.Data.float32 * i;
      VAR->cos_x.Data.float32 = aro_cos(VAR->x.Data.float32); 
      VAR->sin_x.Data.float32 = aro_sin(VAR->x.Data.float32);
      VAR->cos_nx.Data.float32 = VAR->cos_x.Data.float32; 
      VAR->sin_nx.Data.float32 = VAR->sin_x.Data.float32;
      
      VAR->aFourier[0].Data.float32 += VAR->da2.Data.float32;
      VAR->aFourier[1].Data.float32 += VAR->da2.Data.float32 * VAR->cos_x.Data.float32;
      VAR->bFourier[1].Data.float32 += VAR->da2.Data.float32 * VAR->sin_x.Data.float32;
      
      for (j=2; j < nF; j++)
      {
        b1 = VAR->cos_x.Data.float32 * VAR->cos_nx.Data.float32 - VAR->sin_x.Data.float32 * VAR->sin_nx.Data.float32; 
        b2 = VAR->sin_x.Data.float32 * VAR->cos_nx.Data.float32 + VAR->cos_x.Data.float32 * VAR->sin_nx.Data.float32;
        VAR->cos_nx.Data.float32 = b1;
        VAR->sin_nx.Data.float32 = b2;
        VAR->aFourier[j].Data.float32 += VAR->da2.Data.float32 * VAR->cos_nx.Data.float32;
        VAR->bFourier[j].Data.float32 += VAR->da2.Data.float32 * VAR->sin_nx.Data.float32;
      }
    }
    //----------------------------------------------------------------------------
    OUT->Stage.Data.uint8++;
    break;
  case 11:
    LENGTH2 = VAR->LenDNM.Data.uint16 >> 1;
    VAR->aFourier[0].Data.float32 = VAR->aFourier[0].Data.float32 / (2*LENGTH2-1);
    
    for (i=1; i< nF; i++)
    {
      VAR->aFourier[i].Data.float32 = 2 * VAR->aFourier[i].Data.float32 / (2*LENGTH2-1);
      VAR->bFourier[i].Data.float32 = 2 * VAR->bFourier[i].Data.float32 / (2*LENGTH2-1);
    }
    OUT->Stage.Data.uint8++;
    break;
  case 12:      // Стадии работы 
  case 13:      // второго "тяжёлого" цикла
  case 14:
  case 15:
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
    switch (OUT->Stage.Data.uint8)
    {
    case 12:
      LenLo = 1;
      LenHi = 20;
      break;
    case 13:
      LenLo = 20;
      LenHi = 40;
      break;
    case 14:
      LenLo = 40;
      LenHi = 60;
      break;
    case 15:
      LenLo = 60;
      LenHi = 80;
      break;
    case 16:
      LenLo = 80;
      LenHi = 100;
      break;
    case 17:
      LenLo = 100;
      LenHi = 120;
      break;
    case 18:
      LenLo = 120;
      LenHi = 140;
      break;
    case 19:
      LenLo = 140;
      
      if (VAR->LenDNM.Data.uint16 > 160)
        LenHi = 160;
      else
      {
        LenHi = VAR->LenDNM.Data.uint16+1;
        OUT->Stage.Data.uint8 = 21; 
      }
      break;
    case 20:
      LenLo = 160;
      if (VAR->LenDNM.Data.uint16 > 180)
        LenHi = 180;
      else
      {
        LenHi = VAR->LenDNM.Data.uint16+1;
        OUT->Stage.Data.uint8 = 21; 
      }
      break;
    case 21:
      LenLo = 180;
      LenHi = VAR->LenDNM.Data.uint16+1;
      OUT->Stage.Data.uint8 = 21; 
      break;
    }

#ifdef FB64_DEBUG
    DBGU_fprint("CYC2[%d,%d]\r\n", LenLo, LenHi-1);
#endif
    
    //----------- Обработка 92 мс -----------------------------------------------
    for (i=LenLo; i< LenHi; i++)
    {
      VAR->x.Data.float32 = VAR->omega.Data.float32 * i; 
      VAR->cos_x.Data.float32 = aro_cos(VAR->x.Data.float32); 
      VAR->sin_x.Data.float32 = aro_sin(VAR->x.Data.float32); 
      VAR->cos_nx.Data.float32 = VAR->cos_x.Data.float32; 
      VAR->sin_nx.Data.float32 = VAR->sin_x.Data.float32;
      
      VAR->da1.Data.float32 = VAR->aFourier[0].Data.float32 + VAR->aFourier[1].Data.float32 * VAR->cos_x.Data.float32 + VAR->bFourier[1].Data.float32 * VAR->sin_x.Data.float32;
      
      for (j=2; j< nF; j++)
      {
        b1 = VAR->cos_x.Data.float32 * VAR->cos_nx.Data.float32 - VAR->sin_x.Data.float32 * VAR->sin_nx.Data.float32;
        b2 = VAR->sin_x.Data.float32 * VAR->cos_nx.Data.float32 + VAR->cos_x.Data.float32 * VAR->sin_nx.Data.float32;
        VAR->cos_nx.Data.float32 = b1; 
        VAR->sin_nx.Data.float32 = b2;
        VAR->da1.Data.float32 += (VAR->aFourier[j].Data.float32 * VAR->cos_nx.Data.float32 + VAR->bFourier[j].Data.float32 * VAR->sin_nx.Data.float32);
      }
      
      VAR->cond1.Data.float32 = 0.0;
      if (VAR->da1.Data.float32 < VAR->cond1.Data.float32)
        VAR->da1.Data.float32 = 0.0;
      if (VAR->da1.Data.float32 > 255)
        VAR->da1.Data.float32 = 255.0;
      VAR->BufCor_F[i].Data.uint8 = (char) VAR->da1.Data.float32;
    }
    //--------------------------------------------------------------------------
    OUT->Stage.Data.uint8++;
    break;
  case 22:
    //------ Обработка 8 мс ----------------------------------------------------
    LENGTH2 = VAR->LenDNM.Data.uint16 >> 1;
    par_L1 = 0.1; 
    par_L2 = 0.2;
    
    total_area = 0;
    
    for (i=1; i <= LENGTH2; i++)
      total_area += (short) VAR->BufCor_F[i].Data.uint8;
    
    a1 = total_area/2; 
    a2 = 0; 
    iidx1 = 0;
    
    while (a1 > a2)
      a2 += (short) VAR->BufCor_F[iidx1++].Data.uint8; 
    
    iidx1--;
    
    a1 = LENGTH2 - iidx1 + 1; 
    a2 = 0;
    
    for (i=iidx1; i<=LENGTH2; i++)
      a2 += (short) VAR->BufCor_F[i].Data.uint8;
    
    hBScope = a2 / a1;
    
    VAR->P2_idx.Data.uint8 = get_P_idx(-1, 1, iidx1, VAR->BufCor_F); //// ТУТ БЫЛО ЗАВИСАНИЕ!!!
    P4_1_idx = get_P_idx(1, LENGTH2+1, 2*LENGTH2, VAR->BufCor_F);
    P4_2_idx = get_P_idx(1, LENGTH2+1, P4_1_idx-1, VAR->BufCor_F);
    
    if (P4_2_idx < LENGTH2+2)
      P4_2_idx = P4_1_idx - 1;
    
    P4_3_idx = get_P_idx(1, P4_1_idx+1, 2*LENGTH2, VAR->BufCor_F);
    
    if (P4_3_idx >= 2*LENGTH2-5)
      P4_3_idx = P4_1_idx+1;
    
    a1 = P4_3_idx; 
    
    if ((float)(2*LENGTH2-P4_3_idx) < par_L2*(float)(LENGTH2))
    {
      b1 = (float)(P4_3_idx) - (float)(0.2)*(float)(LENGTH2);
      a1 = (short) b1;
    }
    a2 = 0;
    
    for (i=a1; i<=2*LENGTH2; i++)
      a2 += (short) VAR->BufCor_F[i].Data.uint8;
    
    lBScope = a2 / (2*LENGTH2-a1+1);
    Scope_of_dnm = hBScope - lBScope;
    
    b1 = par_L1 * (float)(LENGTH2); 
    b2 = par_L2 * (float)(LENGTH2);
    b3 = (float)(P4_1_idx) - (float)(P4_2_idx) + (float)(1.0);
    b4 = (float)(P4_3_idx) - (float)(P4_1_idx) + (float)(1.0);
    //------------------------------------------------------------------------------  
    
    //---------------- Анализ 17 мс ------------------------------------------------  
    LENGTH2 = VAR->LenDNM.Data.uint16 >> 1;

    if ( (b3<b1) & (b4<b2) )
    {
      //				Случай '1'
      VAR->P4_idx.Data.uint8 = P4_1_idx;
      w1 = (float) VAR->BufCor_F[P4_2_idx].Data.uint8 - (float) VAR->BufCor_F[P4_1_idx].Data.uint8;
      w1 = w1 / (float)(255.0); 
      w2 = (float)(0.1);
      if (w1 < w2)
        VAR->P4_idx.Data.uint8 = P4_2_idx;
    }
    else
    {
      aro_polyfit3(1, P4_3_idx-LENGTH2, VAR->BufCor_F, LENGTH2, &c3_1, &c3_2, &c3_3, &c3_4);
      
      VAR->roo.Data.float32 = -c3_2 / ((float)(3.0) * c3_1); 
      
      if ( (VAR->roo.Data.float32 <= 1) || (VAR->roo.Data.float32 >= (P4_3_idx-LENGTH2)) )
        VAR->roo.Data.float32 = -1;
      
      b1 = (VAR->roo.Data.float32-(float)(1.0)) / ((float) P4_3_idx - VAR->roo.Data.float32 - (float) LENGTH2);
      b2 = ((float) P4_3_idx - VAR->roo.Data.float32 - (float) LENGTH2) / (VAR->roo.Data.float32 - 1);
      
      if (b1 > (float)(1.7) | b2 > (float)(1.7))
        VAR->roo.Data.float32 = -1;
      
      if ((float)(P4_1_idx-P4_2_idx+1) < par_L1*(float)(LENGTH2) & (float)(P4_3_idx-P4_1_idx+1) >= par_L2*(float)(LENGTH2))
      {
        //				Случай '2'
        if (VAR->roo.Data.float32 != (float)(-1.0))
        {
          VAR->d1.Data.float32 = ((float)(1.0) + VAR->roo.Data.float32)/(float)(2.0);
          VAR->d2.Data.float32 = (VAR->roo.Data.float32 + (float)(P4_3_idx-LENGTH2))/(float)(2.0);
          VAR->d1.Data.float32 = (float)(6.0) * c3_1 * VAR->d1.Data.float32 + (float)(2.0) * c3_2;
          VAR->d2.Data.float32 = (float)(6.0) * c3_1 * VAR->d2.Data.float32 + (float)(2.0) * c3_2;
          
          if ((VAR->d1.Data.float32 < 0) && (VAR->d2.Data.float32 > 0))
          {
            a1 = P4_2_idx-LENGTH2 - (short) VAR->roo.Data.float32; 
            a2 = P4_2_idx;
            if (a1 < 0)
            {
              a1 = P4_1_idx - LENGTH2 - (short)VAR->roo.Data.float32; 
              a2 = P4_1_idx;
            }
            
            if (a1 < 0)
            {
              a1 = P4_3_idx - LENGTH2 - (short)VAR->roo.Data.float32; 
              a2 = P4_3_idx;
            }
            VAR->P4_idx.Data.uint8 = a2;
          }
          else
          {
            VAR->P4_idx.Data.uint8 = P4_1_idx; 
            VAR->cond1.Data.float32 = ((float)(VAR->BufCor_F[(int)(VAR->roo.Data.float32)+LENGTH2].Data.uint8) - (float)(lBScope)) / (float)(Scope_of_dnm);
            
            if (VAR->cond1.Data.float32 >= 0.25)
              VAR->P4_idx.Data.uint8 = P4_3_idx; 
            
            if ( (VAR->cond1.Data.float32 < 0.25) && (VAR->cond1.Data.float32 > 0.15) )
            {
              aro_polyfit1(P4_1_idx-LENGTH2, (short)(VAR->roo.Data.float32), VAR->BufCor_F, LENGTH2, &c1_1, &c1_2);
              aro_polyfit1(P4_1_idx-LENGTH2, P4_3_idx-LENGTH2, VAR->BufCor_F, LENGTH2, &c2_1, &c2_2);
              b1 = c1_1*(float)(P4_3_idx-LENGTH2) + c1_2;
              b2 = c2_1*(float)(P4_3_idx-LENGTH2) + c2_2;
              
              b1 = (b1-b2) / (float)(250.0);
              
              if (b1 > (float)(0.1))
                VAR->P4_idx.Data.uint8 = P4_3_idx;
            }
          }
        }
        else
        {
          a1 = (LENGTH2+1+P4_3_idx)/2;
          VAR->d1.Data.float32 = (float)(a1) - (float)(LENGTH2);
          VAR->d1.Data.float32 = (float)(6.0) * c3_1 * VAR->d1.Data.float32 + (float)(2.0) * c3_2;
          if (VAR->d1.Data.float32 < 0)
          {
            VAR->P4_idx.Data.uint8 = P4_1_idx;
            VAR->d2.Data.float32 = (float)(VAR->BufCor_F[P4_1_idx].Data.uint8) - (float)lBScope;
            VAR->d2.Data.float32 = VAR->d2.Data.float32 / (float)Scope_of_dnm;
            if (VAR->d2.Data.float32 > 0.2)
              VAR->P4_idx.Data.uint8 = P4_3_idx;
          }
          else
          {
            aro_polyfit2(P4_2_idx-LENGTH2, P4_3_idx-LENGTH2, VAR->BufCor_F,LENGTH2, &c2_1, &c2_2, &c2_3);
            for (i = P4_2_idx-LENGTH2; i <= P4_1_idx-LENGTH2; i++)
            {
              VAR->da1.Data.float32 = c2_1 * (float)i * (float)i + c2_2 * (float)i + c2_3;
              b1 = (float)(VAR->BufCor_F[i+LENGTH2].Data.uint8);
              if (b1 < VAR->da1.Data.float32)
              {             /////////
                VAR->P4_idx.Data.uint8 = i + LENGTH2; 
                break;
              }
            }
          }
        }
      }
      
      if ((float)(P4_1_idx - P4_2_idx + 1) >= par_L1*(float)(LENGTH2) & (float)(P4_3_idx - P4_1_idx + 1) < par_L2 * (float)LENGTH2)
      {
        //				Случай '3'
        if (VAR->roo.Data.float32 != (float)(-1.0))
        {
          VAR->d1.Data.float32 = ((float)(1.0)+VAR->roo.Data.float32) / (float)(2.0);
          VAR->d2.Data.float32 = (VAR->roo.Data.float32 + (float)(P4_3_idx-LENGTH2)) / (float)(2.0);
          VAR->d1.Data.float32 = (float)(6.0) * c3_1 * VAR->d1.Data.float32 + (float)(2.0) * c3_2;
          VAR->d2.Data.float32 = (float)(6.0) * c3_1 * VAR->d2.Data.float32 + (float)(2.0) * c3_2;
          if ((VAR->d1.Data.float32 < 0) && (VAR->d2.Data.float32 > 0))
          {
            a1 = P4_2_idx - LENGTH2 - (short)VAR->roo.Data.float32; 
            a2 = P4_2_idx;
            
            if (a1 < 0)
            {
              a1 = P4_1_idx - LENGTH2 - (short)VAR->roo.Data.float32; 
              a2 = P4_1_idx;
            }
            
            if (a1 < 0)
            {
              a1 = P4_3_idx - LENGTH2 - (short)VAR->roo.Data.float32; 
              a2 = P4_3_idx;
            }
            
            VAR->P4_idx.Data.uint8 = a2;
          }
          else
          {
            aro_polyfit2(P4_2_idx-LENGTH2, P4_1_idx-LENGTH2, VAR->BufCor_F, LENGTH2, &c2_1, &c2_2, &c2_3);
            VAR->da1.Data.float32 = (float)(P4_2_idx-LENGTH2); 
            VAR->da1.Data.float32 = c2_1 * VAR->da1.Data.float32 * VAR->da1.Data.float32 + c2_2 * VAR->da1.Data.float32 + c2_3;
            VAR->da2.Data.float32 = (float)(P4_1_idx-LENGTH2); 
            VAR->da2.Data.float32 = c2_1 * VAR->da2.Data.float32 * VAR->da2.Data.float32 + c2_2 * VAR->da2.Data.float32 + c2_3;
            VAR->cond1.Data.float32 = (VAR->da1.Data.float32 - VAR->da2.Data.float32) / (float)Scope_of_dnm;
            VAR->P4_idx.Data.uint8 = P4_2_idx; 
            if (VAR->cond1.Data.float32 > 0.15)
              VAR->P4_idx.Data.uint8 = P4_1_idx; 
          }
        }
        else
        {
          a1 = (LENGTH2+1+P4_3_idx)/2;
          VAR->d1.Data.float32 = (float)(a1-LENGTH2); 
          VAR->d1.Data.float32 = (float)(6.0) * c3_1 * VAR->d1.Data.float32 + (float)(2.0)*c3_2;

          if (VAR->d1.Data.float32 < (float)(0.0))
          {
            VAR->P4_idx.Data.uint8 = P4_1_idx;
          }
          else
          {
            VAR->P4_idx.Data.uint8 = P4_1_idx; 
            VAR->cond1.Data.float32 = ((float)(VAR->BufCor_F[P4_2_idx].Data.uint8)-(float)(lBScope)) / (float)Scope_of_dnm;
            if (VAR->cond1.Data.float32 <= 0.1)
              VAR->P4_idx.Data.uint8 = P4_2_idx;
            if ((VAR->cond1.Data.float32 < 0.25) & (VAR->cond1.Data.float32 > 0.1))
            {
              a1 = P4_1_idx - P4_2_idx; 
              a1 = P4_2_idx - a1;
              
              if (a1 < LENGTH2 + 1)
                a1 = LENGTH2 + 1;
              
              a2 = P4_1_idx - P4_2_idx; 
              a2 = P4_3_idx + a1; 
              
              if (a2 > 2*LENGTH2)
                a2 = 2*LENGTH2;
              
              aro_polyfit1(a1-LENGTH2, a2-LENGTH2, VAR->BufCor_F, LENGTH2, &c1_1, &c1_2);
              VAR->da1.Data.float32 = c1_1*((float)(P4_2_idx-LENGTH2)) + c1_2 - (float)(VAR->BufCor_F[P4_2_idx].Data.uint8);
              VAR->da2.Data.float32 = c1_1*((float)(P4_1_idx-LENGTH2)) + c1_2 - (float)(VAR->BufCor_F[P4_1_idx].Data.uint8);
              VAR->da1.Data.float32 = VAR->da1.Data.float32 / VAR->da2.Data.float32;

              if (VAR->da1.Data.float32 > (float)(0.5))
              {
                VAR->P4_idx.Data.uint8 = P4_2_idx; 
              }
            }
          }
        }
      }
      
      if ((float)(P4_1_idx-P4_2_idx+1) >= par_L1*(float)(LENGTH2) & (float)(P4_3_idx-P4_1_idx+1) >= par_L2*(float)(LENGTH2))
      {
        //				Случай '4'
        if (VAR->roo.Data.float32 != (float)(-1.0))
        {
          //						Случай '4_1'
          VAR->d1.Data.float32 = ((float)(1.0) + VAR->roo.Data.float32) / (float)(2.0);
          VAR->d2.Data.float32 = (VAR->roo.Data.float32 + (float)(P4_3_idx-LENGTH2)) / (float)(2.0);
          VAR->d1.Data.float32 = (float)(6.0) * c3_1 * VAR->d1.Data.float32 + (float)(2.0) * c3_2;
          VAR->d2.Data.float32 = (float)(6.0) * c3_1 * VAR->d2.Data.float32 + (float)(2.0) * c3_2;
          if ((VAR->d1.Data.float32 < 0) && (VAR->d2.Data.float32 > 0))
          {
            a1 = P4_2_idx - LENGTH2 - (short)VAR->roo.Data.float32; 
            a2 = P4_2_idx;
            if (a1<0)
            {
              a1 = P4_1_idx - LENGTH2 - (short)VAR->roo.Data.float32; 
              a2 = P4_1_idx;
            }
            if (a1 < 0)
            {
              a1 = P4_3_idx - LENGTH2 - (short)VAR->roo.Data.float32; 
              a2 = P4_3_idx;
            }
            VAR->P4_idx.Data.uint8 = a2;
          }
          else
          {
            aro_polyfit2((short)VAR->roo.Data.float32, P4_3_idx-LENGTH2, VAR->BufCor_F, LENGTH2, &c2_1, &c2_2, &c2_3);
            VAR->cond1.Data.float32 = ((float)(VAR->BufCor_F[(short)VAR->roo.Data.float32 + LENGTH2].Data.uint8) - (float)(VAR->BufCor_F[P4_3_idx].Data.uint8))/(float)(Scope_of_dnm);
            if ((c2_1 < (-0.05)) && (VAR->cond1.Data.float32 > 0.13))
              VAR->P4_idx.Data.uint8 = P4_3_idx; 
            else
            {
              aro_polyfit2(P4_2_idx-LENGTH2, P4_3_idx-LENGTH2, VAR->BufCor_F, LENGTH2, &c2_1, &c2_2, &c2_3);
              for (i=P4_2_idx-LENGTH2; i <= P4_1_idx-LENGTH2; i++)
              {
                VAR->da1.Data.float32 = c2_1*(float)(i)*(float)(i) + c2_2*(float)(i) + c2_3;
                if ((float)(VAR->BufCor_F[i+LENGTH2].Data.uint8) < VAR->da1.Data.float32)
                {
                  VAR->P4_idx.Data.uint8 = i + LENGTH2; 
                  break;
                }
              }
            }
          }
        }
        else
        {
          a1 = (LENGTH2+1+P4_3_idx)/2;
          VAR->d1.Data.float32 = (float)(a1-LENGTH2); 
          VAR->d1.Data.float32 = (float)(6.0) * c3_1 * VAR->d1.Data.float32 + (float)(2.0)*c3_2;

          if (VAR->d1.Data.float32 < 0)
          {
            VAR->P4_idx.Data.uint8 = P4_1_idx;
            if ((float)(VAR->BufCor_F[P4_1_idx].Data.uint8-lBScope)/(float)(Scope_of_dnm) > (float)(0.2))
            {
              VAR->P4_idx.Data.uint8 = P4_3_idx;
            }
          }
          else
          {
            VAR->P4_idx.Data.uint8 = P4_1_idx; 
            aro_polyfit2(P4_2_idx-LENGTH2, P4_3_idx-LENGTH2, VAR->BufCor_F, LENGTH2, &c2_1, &c2_2, &c2_3);
            VAR->da1.Data.float32 = (float)(P4_2_idx-LENGTH2);
            VAR->da1.Data.float32 = c2_1 * VAR->da1.Data.float32 * VAR->da1.Data.float32 + c2_2 * VAR->da1.Data.float32 + c2_3;
            VAR->da2.Data.float32 = (float)(P4_1_idx-LENGTH2);
            VAR->da2.Data.float32 = c2_1 * VAR->da2.Data.float32 * VAR->da2.Data.float32 + c2_2 * VAR->da2.Data.float32 + c2_3;
            
            VAR->cond1.Data.float32 = (VAR->da1.Data.float32 - VAR->da2.Data.float32)/(float)Scope_of_dnm;
            
            if (VAR->cond1.Data.float32 < 0.4)
            {
              aro_polyfit2(P4_1_idx-LENGTH2, P4_3_idx-LENGTH2, VAR->BufCor_F,LENGTH2, &c2_1_1, &c2_1_2, &c2_1_3);						
              VAR->da1.Data.float32 = (float)(P4_1_idx-LENGTH2);
              VAR->da1.Data.float32 = c2_1_1 * VAR->da1.Data.float32 * VAR->da1.Data.float32 + c2_1_2 * VAR->da1.Data.float32 + c2_1_3;
              VAR->da2.Data.float32 = (float)(P4_3_idx-LENGTH2);
              VAR->da2.Data.float32 = c2_1_1 * VAR->da2.Data.float32 * VAR->da2.Data.float32 + c2_1_2 * VAR->da2.Data.float32 + c2_1_3;
              VAR->cond1.Data.float32 = (VAR->da1.Data.float32 - VAR->da2.Data.float32) / (float)Scope_of_dnm;
              a2 = 0; 
              
              if ((c2_1_1 < 0) && (VAR->cond1.Data.float32 > 0.15))
                a2 = 1;
              
              if (a2 > 0)
              {
                a2 = 0; 
                a1 = get_P_idx(-1, P4_1_idx, P4_3_idx, VAR->BufCor_F);
                aro_polyfit1(P4_1_idx-LENGTH2, a1-LENGTH2, VAR->BufCor_F, LENGTH2, &c1_1_1, &c1_2_1);
                aro_polyfit1(a1-LENGTH2, P4_3_idx-LENGTH2, VAR->BufCor_F, LENGTH2, &c1_1_2, &c1_2_2);
                VAR->cond1.Data.float32 = -(c1_1_2-c1_1_1) * (float)(180.0) / (float)(3.14159265358979);
                
                if ( (c1_1_1 < 0) && (c1_1_2 < 0) && (VAR->cond1.Data.float32 > 120) )
                  a2 = 1;
              }
              
              if (a2>0)
              {
                VAR->P4_idx.Data.uint8 = P4_3_idx;
              }
              else
              {
                for (i=P4_2_idx-LENGTH2; i <= P4_1_idx-LENGTH2; i++)
                {
                  VAR->da1.Data.float32 = c2_1*(float)(i)*(float)(i) + c2_2*(float)(i) + c2_3;
                  if ((float)(VAR->BufCor_F[i+LENGTH2].Data.uint8) < VAR->da1.Data.float32)
                  {
                    VAR->P4_idx.Data.uint8 = i + LENGTH2; 
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
    //------------------------------------------------------------------------------
    
    // Расчет коэффициента наполнения
    //----------------- Расчёты 0.3 мс -------------------------------------------
    // Полагаем T = 1, L = 1
    b1 = (float)(VAR->P2_idx.Data.uint8-1) / (float)(VAR->LenDNM.Data.uint16-1);		//время (P2_idx) при T=1, L=1
    
    //перемещение (P2_idx) при T=1, L=1
    b1 = ((float)(1.0) - aro_cos((float)(2.0) * (float)(3.14159265358979)*b1)) / 2;
    b1 = (float)(1.0) - b1;		//длина хода плунжера, при T=1, L=1
    b2 = (float)(VAR->P4_idx.Data.uint8 - 1) / (float)(VAR->LenDNM.Data.uint16-1);		//время (P4_idx) при T=1, L=1
    
    //перемещение (P4_idx) при T=1, L=1
    b2 = ((float)(1.0) - aro_cos((float)(2.0) * (float)(3.14159265358979) * b2)) / 2;
    b1 = (float)(100.0) * b2 / b1;
    
    OUT->Knap.Data.uint8 = (unsigned char)b1;
    
    if (OUT->Knap.Data.uint8 > 100) 
      OUT->Knap.Data.uint8 = 100;
    
    //---------------------------------------------------------------------------  
    
#ifdef FB64_DEBUG
    DBGU_fprint("Knap[%d,%d]=%d\n\r", VAR->P2_idx.Data.uint8, VAR->P4_idx.Data.uint8, OUT->Knap.Data.uint8);
#endif
    
    OUT->KnapOK.Data.bit = 1;
    OUT->Stage.Data.uint8 = 0;
    break;
  default:
    OUT->Stage.Data.uint8 = 0;
    break;
  }
}

//===
float aro_cos_1(float x, float epsilon)
{
  static float res, x_add, x_deg;
  static float a1, a2, nfact;
  static short m1;
  static unsigned long iter;
  
  res = 1.0; 
  m1 = 1; 
  nfact = 1.0; 
  x_add = x * x; 
  x_deg = 1.0; 
  iter = 0; 
  a1 = 0.0;
  a2 = a1 - res; 
  
  if (a2 < 0)
    a2 = -a2;

  while (a2 > epsilon)
  {
    iter = iter + 1; 
    m1 = -m1; 
    nfact = nfact*(2*iter-1) * 2*iter; 
    a1 = x_deg / (float)nfact;
    a1 = res + (float)(m1)*a1*x_add;
    x_deg = x_deg * x_add;
    a2 = a1 - res; 
    
    if (a2 < 0)
      a2 = -a2;

    res = a1;
  }
  return res;
}

//=== 
float aro_sin_1(float x, float epsilon)
{
  static float res, x_add, x_deg;
  static float a1, a2, nfact;
  static short m1;
  static unsigned long iter;
  
  res = x; 
  m1 = 1; 
  nfact = 1.0; 
  x_add = x * x; 
  x_deg = x; 
  iter = 0; 
  a1 = 0.0;
  a2 = a1 - res; 
  
  if (a2 < 0)
    a2 = -a2;
  
  while(a2 > epsilon)
  {
    iter = iter + 1; 
    m1 = -m1; 
    nfact = nfact*((float)(2.0)*(float)(iter)+1)*(float)(2.0)*(float)iter; 
    x_deg = x_deg * x_add;
    a1 = res + (float)(m1) * x_deg/nfact;
    a2 = a1 - res; 
  
    if (a2 < 0)
      a2 = -a2;

    res = a1;
  }
  return res;
}

//===
float aro_sin(float x)
{
  static int a1, i;
  static float res, b1, b2, epsilon;
  static float cos_1, sin_1;
  static float cos_n, sin_n;
  static float cond1, cond2;
  
  res = 1.0; 
  cos_1 = 0.54030230586814;
  sin_1 = 0.841470984807897; 
  epsilon = 0.0001; 
  cond1 = 0.0; 
  cond2 = 1.0;
	
  if (x < cond1)
  {
    x = -x; 
    res = -res;
  }
  
  if (x <= cond2)
    res = res * aro_sin_1(x, epsilon);
  
  if (x > cond2)
  {
    a1 = (int) x;
    cos_n = cos_1; 
    sin_n = sin_1;
    for (i=2; i <= a1; i++)
    {
      b1 = cos_1*cos_n - sin_1*sin_n;
      b2 = sin_1*cos_n + cos_1*sin_n;
      cos_n = b1; 
      sin_n = b2;
    }
    res = res * (sin_n * aro_cos_1(x - (float)a1, epsilon) + cos_n * aro_sin_1(x-(float)a1, epsilon));
  }
  return res;
}

//===
float aro_cos(float x)
{
  static float res, b1, b2, epsilon;
  static float cos_1, sin_1;
  static float cos_n, sin_n;
  static int a1, i;
  static float cond1, cond2;
  
  cos_1 = 0.54030230586814; 
  sin_1 = 0.841470984807897;
  epsilon = 0.0001;
  cond1 = 0.0; 
  cond2 = 1.0;
	
  if (x < cond1)
    x = -x;
	
  if (x <= cond2)
    res = aro_cos_1(x, epsilon);
	
  if (x > cond2)
  {
    a1 = (int) x;
    cos_n = cos_1; 
    sin_n = sin_1;
    for (i=2; i<=a1; i++)
    {
      b1 = cos_1*cos_n - sin_1*sin_n;
      b2 = sin_1*cos_n + cos_1*sin_n;
      cos_n = b1; 
      sin_n = b2;
    }
    res = cos_n * aro_cos_1(x-(float) a1, epsilon) - sin_n * aro_sin_1(x-(float) a1, epsilon);
  }
  return res;
}

//===
float aro_sqrt_1(float x, float epsilon)
{
  static float x_, res, nfact, x_deg, alfa, alfas;
  static float a1, a2, cond1;
  static float iter;
  
  nfact = (float)(1.0); 
  iter = (float)(0.0); 
  x_deg = (float)(1.0);
  res = (float)(1.0); 
  x_= x - (float)(1.0);
  alfa = (float)(0.5);
  alfas = (float)(1.0); 
  a1 = (float)(0.0);
  a2 = a1 - res; 
  cond1 = (float)(0.0);
  
  if (a2 < cond1)
    a2 = -a2;

  while (a2 > epsilon & iter <= 70)
  {
    iter = iter + (float)(1.0);
    nfact = nfact * iter; 
    x_deg = x_deg * x_; 
    alfas = alfas * (alfa - iter + (float)(1.0));
    a1 = res + x_deg * alfas / nfact;
    a2 = a1 - res; 

    if (a2 < cond1)
      a2 = -a2;

    res = a1;
  }
  return res;
}

//===
float aro_sqrt(float x)
{
  static float xx, ab, res;
  static int nn, i;
  static float epsilon, cond1;
  
  cond1 = (float)(2.0); 
  epsilon = (float)(0.0001);
  
  if (x < cond1)
    res = aro_sqrt_1(x, epsilon);

  if (x >= cond1)
  {
    xx = x; 
    ab = (float)(0.96); 
    nn = 0;
    while (xx > 2)
    {
      nn = nn + 1; 
      xx = xx / ((float)(1.0) + ab);
    }
    res = (float)(1.0); 
    for (i=1; i <= nn; i++) 
      res = res * (float)(1.4);
    res = res * aro_sqrt_1(xx, epsilon);
  }
  return res;
}

//=== 
unsigned char get_P_idx(short cside, unsigned char i_start, unsigned char i_end, Register_type y_1[])
{
  static unsigned char P_idx, i;
  static float k, b, a1, a3, delta, sign_cside, cond1;
  
  k = ((float)(y_1[i_end].Data.uint8) - (float)(y_1[i_start].Data.uint8)) / ((float)i_end - (float)i_start);

  b = (float)(y_1[i_start].Data.uint8) - k * (float)i_start;
  cond1 = (float)(0.0);
  sign_cside = (float)(1.0);
  
  if (cside < cond1)
    sign_cside = -sign_cside;
  
  a3 = (float)(0.0); 
  P_idx = i_start; 
  a1 = aro_sqrt((float)(1.0) + k * k);

  for (i=i_start; i <= i_end; i++)
  {
    delta = sign_cside * ((float)(i) * k / a1 - (float)(y_1[i].Data.uint8)/a1+b/a1);
    if (delta > a3)
    {
      P_idx = i; 
      a3 = delta;
    }
  if (i == 255) 
    break; //// Костыль
  }
  return P_idx;

}

//===
float aro_eml_sub2norm(float x[], int istart, int iend)
{
  float y, scale, absx, temp, cond1;
  int k;
	
  y = (float)(0.0); 
  scale = (float)(0.0); 
  cond1 = (float)(0.0);
  
  for (k = istart; k <= iend; k++)
  {
    absx = x[k]; 
    if (absx < cond1)
      absx = -absx;
    
    if (absx > cond1)
    {
      if (scale < absx)
      {
        temp = scale / absx;
        y = (float)(1.0) + y * temp * temp;
        scale = absx;
      }
      else
      {
        temp = absx / scale;
        y = y + temp * temp;
      }
    }
  }
  y = scale * aro_sqrt(y);
  return y;
}

//===
float get_beta(float alphr, float xnorm)
{
  float beta, a, b, a1, cond1;
  
  a = alphr; 
  cond1 = (float)(0.0);
  
  if (a < cond1)
    a = -a;

  b = xnorm; 

  if (b < cond1)
    b = -b;

  a1 = a; 
  if (a > b)
  {
    a = b; 
    b = a1;
  }
	
  a = a / b; 
  beta = b * aro_sqrt((float)(1.0) + a * a);

  if (alphr >= cond1)
    beta = -beta;

  return beta;
}

//===
void aro_polyfit1(int xstart, int xend, Register_type y[], short off_y, float *c1, float *c2)
{
#define LENGTH_Ar	150
  int i, m;
  float A[2*LENGTH_Ar], R[5];
  float xnorm, alphr, beta, wj1;
  float betas[3], alphas[3], tau[3];
  float detR, a11, a21, a22;
  
  m = xend - xstart + 1;
  for (i = xstart; i <= xend; i++)
  {
    A[i-xstart+1] = (float) i; 
    A[i-xstart+1+m] = (float)(1.0);
  }
  
  xnorm = aro_eml_sub2norm(A, 2, m);
  alphr = A[1];
  beta = get_beta(alphr, xnorm);
  betas[1] = beta;
  tau[1] = (betas[1] - alphr) / betas[1];
  alphas[1] = (float)(1.0) / (alphr - betas[1]);
  wj1 = A[m+1];
  
  for (i = 2; i <= m; i++)
  {
    A[i] = A[i] * alphas[1];
    wj1 = wj1 + A[i] * A[i+m];
  }
	
  wj1 = tau[1] * wj1;
	
  for (i = m+2; i <= 2*m; i++)
    A[i] = A[i] - A[i-m] * wj1;

  xnorm = aro_eml_sub2norm(A, m+3, 2*m);
  alphr = A[m+2]; 
  beta = get_beta(alphr, xnorm);
  betas[2] = beta;
  tau[2] = (betas[2] - alphr) / betas[2];
  alphas[2] = (float)(1.0)/(alphr - betas[2]);
  
  for (i = m+3; i <= 2*m; i++)
    A[i] = A[i] * alphas[2];

  A[1] = betas[1]; 
  A[m+2] = betas[2]; 
  A[m+1] = A[m+1] - wj1;
  
  R[1] = A[1]; 
  R[2] = (float)(0.0); 
  R[3] = A[m+1]; 
  R[4] = A[m+2];
  
  detR = R[1] * R[4]; 
  a11 = R[4] / detR; 
  a21 = R[3] / detR; 
  a22 = R[1] / detR;
  
  R[1] = a11; 
  R[2] = (float)(0.0); 
  R[3] = -a21; 
  R[4] = a22;

  wj1 = (float)(0.0);
  
  for (i = m+3; i <= 2*m; i++)
  {
    A[i] = -A[i] * tau[2];
    wj1 = wj1 + A[i] * A[i-m];
  }
  
  A[m+2] = 1 - tau[2]; 
  A[m+1] = (float)(0.0);
  wj1 = tau[1] * (wj1 + A[m+2] * A[2]);
  
  if (wj1 != (float)(0.0))
  {
    A[m+1] = A[m+1] - wj1;
    for (i = m+2; i <= 2*m; i++)
      A[i] = A[i] - A[i-m] * wj1;
  }

  for (i = 2; i <= m; i++)
    A[i] = -A[i] * tau[1];

  A[1] = (float)(1.0) - tau[1];
  
  a21 = (float)(0.0); 
  a22 = (float)(0.0);
  
  for (i = 1; i <= m; i++)
  {
    a21 = a21 + A[i] * (float)(y[xstart+i-1+off_y].Data.uint8);
    a22 = a22 + A[i+m] * (float)(y[xstart+i-1+off_y].Data.uint8);
  }
  *c1 = R[1] * a21 + R[3] * a22;
  *c2 = R[2] * a21 + R[4] * a22;
}

//===
void aro_polyfit2(int xstart, int xend, Register_type y[], short off_y, float *c1, float *c2, float *c3)
{
#define LENGTH_Ar	150
  int i, m;
  static float A[3*LENGTH_Ar], R[10];
  static float di;
  static float alphas[4], betas[4], wjs[4], tau[4];
  static float xnorm, alphr, beta;
  static float wj1, wj2, wj3;
  static float detR, a11, a21, a22, a31, a32, a33;
  
  m = xend - xstart + 1;
  for (i = xstart; i <= xend; i++)
  {
    di = (float) i;
    A[i-xstart+1] = di*di; 
    A[i-xstart+1+m] = di; 
    A[i-xstart+1+2*m] = (float)(1.0);
  }
  
  xnorm = aro_eml_sub2norm(A, 2, m); 
  alphr = A[1];
  beta = get_beta(alphr, xnorm); 
  betas[1] = beta;
  tau[1] = (betas[1] - alphr) / betas[1];
  alphas[1] = (float)(1.0) / (alphr - betas[1]);
  wj1 = A[m+1]; 
  wj2 = A[2*m+1];
  for (i = 2; i <= m; i++) 
  {
    A[i] = A[i] * alphas[1];
    wj1 = wj1 + A[i] * A[i+m];
    wj2 = wj2 + A[i] * A[i+2*m];
  }
  wjs[1] = tau[1] * wj1; 
  wjs[2] = tau[1] * wj2;
  for (i = m+2; i <= 2*m; i++)
  {
    A[i] = A[i] - A[i-m] * wjs[1];
    A[i+m] = A[i+m] - A[i-m] * wjs[2];
  }
  
  xnorm = aro_eml_sub2norm(A, m+3, 2*m); 
  alphr = A[m+2];
  beta = get_beta(alphr, xnorm); 
  betas[2] = beta;
  tau[2] = (betas[2] - alphr) / betas[2];
  alphas[2] = (float)(1.0) / (alphr - betas[2]);
  wj1 = A[2*m+2];
  
  for (i = m+3; i <= 2*m; i++)
  {
    A[i] = A[i] * alphas[2];
    wj1 = wj1 + A[i] * A[i+m];
  }
	
  wjs[3] = tau[2] * wj1;
	
  for (i = 2*m+3; i <= 3*m; i++)
    A[i] = (A[i] - A[i-m] * wjs[3]);

  xnorm = aro_eml_sub2norm(A, 2*m+4, 3*m); 
  alphr = A[2*m+3];
  beta = get_beta(alphr, xnorm); 
  betas[3] = beta;
  tau[3] = (betas[3] - alphr) / betas[3];
  alphas[3] = (float)(1.0) / (alphr - betas[3]);
  
  for (i = 2*m+4; i <= 3*m; i++)
    A[i] *= alphas[3];

  A[1] = betas[1]; 
  A[m+2] = betas[2]; 
  A[2*m+3] = betas[3];

  A[m+1] = A[m+1] - wjs[1]; 
  A[2*m+1] = A[2*m+1] - wjs[2];
  A[2*m+2] = A[2*m+2] - wjs[3];

  R[1] = A[1]; 
  R[2] = (float)(0.0); 
  R[3] = (float)(0.0);
  R[4] = A[m+1]; 
  R[5] = A[m+2]; 
  R[6] = (float)(0.0);
  R[7] = A[2*m+1]; 
  R[8] = A[2*m+2]; 
  R[9] = A[2*m+3];

  wj3 = (float)(0.0);
  
  for (i = 2*m+4; i <= 3*m; i++)
  {
    A[i] = -A[i] * tau[3];
    wj3 = wj3 + A[i] * A[i-m];
  }
	
  A[2*m+3] = (float)(1.0) - tau[3]; 
  A[2*m+1] = (float)(0.0); 
  A[2*m+2] = (float)(0.0); 
  wj3 = tau[2] * (wj3+A[2*m+3] * A[m+3]);
  if (wj3 != (float)(0.0))
  {
    A[2*m+2] = A[2*m+2] - wj3;
    for (i = 2*m+3; i <= 3*m; i++)
      A[i] = A[i] - A[i-m] * wj3;
  }

  wj1 = (float)(0.0); 
  wj2 = (float)(0.0);
	
  for (i = m+3; i <= 2*m; i++)
  {
    A[i] = -A[i] * tau[2];
    wj1 = wj1+A[i] * A[i-m];
    wj2 = wj2+A[i+m] * A[i-m];
  }
  
  A[m+2] = (float)(1.0) - tau[2]; 
  A[m+1] = (float)(0.0);
  
  wj1 = tau[1] * (wj1 + A[m+2] * A[2]);
  wj2 = tau[1] * (wj2 + A[2*m+2] * A[2]);
  
  if (wj1 != (float)(0.0))
    A[m+1] = A[m+1] - wj1;

  if (wj2 != (float)(0.0))
    A[2*m+1] = A[2*m+1] - wj2;
	
  for (i = m+2; i <= 2*m; i++)
  {
    if (wj1 != (float)(0.0))
      A[i] = A[i] - A[i-m] * wj1;
    
    if (wj2 != (float)(0.0))
      A[i+m] = A[i+m] - A[i-m] * wj2;
  }
  
  for (i = 2; i <= m; i++)
    A[i] = -A[i] * tau[1];

  A[1] = (float)(1.0) - tau[1];

  detR = R[1] * R[5] * R[9];
  a11 = R[5] * R[9] / detR; 
  a21 = R[4] * R[9] / detR; 
  a22 = R[1] * R[9] / detR;
  a31 = (R[4] * R[8] - R[5] * R[7]) / detR;
  a32 = R[1] * R[8] / detR; 
  a33 = R[1] * R[5] / detR;
  
  R[1] = a11; 
  R[2] = (float)(0.0); 
  R[3] = (float)(0.0);
  R[4] = -a21; 
  R[5] = a22; 
  R[6] = (float)(0.0);
  R[7] = a31; 
  R[8] = -a32; 
  R[9] = a33;
	
  a31 = (float)(0.0); 
  a32 = (float)(0.0); 
  a33 = (float)(0.0);
  
  for (i = 1; i <= m; i++)
  {
    a31 = a31 + A[i] * (float)(y[xstart+i-1+off_y].Data.uint8);
    a32 = a32 + A[i+m] * (float)(y[xstart+i-1+off_y].Data.uint8);
    a33 = a33 + A[i+2*m] * (float)(y[xstart+i-1+off_y].Data.uint8);
  }
  
  *c1 = R[1] * a31 + R[4] * a32 + R[7] * a33;
  *c2 = R[2] * a31 + R[5] * a32 + R[8] * a33;
  *c3 = R[3] * a31 + R[6] * a32 + R[9] * a33;
}

//===
void aro_polyfit3(int xstart, int xend, Register_type y[], short off_y, float *c1, float *c2, float *c3, float *c4)
{
#define LENGTH_Ar	150
  int i, m;
  static float A[4*LENGTH_Ar], R[17];
  static float di;
  static float xnorm, alphr, beta;
  static float betas[5], alphas[5], tau[5], wjs[7];
  static float wj1, wj2, wj3, wj4;
  static float detR, a11, a21, a22, a31, a32, a33, a41, a42, a43, a44;
	
  m = xend - xstart + 1;
	
  for (i = xstart; i <= xend; i++)
  {
    di = (double) i;
    A[i-xstart+1] = di * di * di; 
    A[i-xstart+1+m] = di * di;
    A[i-xstart+1+2*m] = di; 
    A[i-xstart+1+3*m] = 1;
  }
  xnorm = aro_eml_sub2norm(A, 2, m); 
  alphr = A[1];
  beta = get_beta(alphr, xnorm); 
  betas[1] = beta;
  
  tau[1] = (betas[1] - alphr) / betas[1]; 
  alphas[1] = (float)(1.0) / (alphr - betas[1]);
  wj1 = A[m+1]; 
  wj2 = A[2*m+1]; 
  wj3 = A[3*m+1];
  for (i = 2; i <= m; i++)
  {
    A[i] = A[i]*alphas[1];
    wj1 = wj1 + A[i] * A[i+m];
    wj2 = wj2 + A[i] * A[i+2*m];
    wj3 = wj3 + A[i] * A[i+3*m];
  }
  wjs[1] = tau[1] * wj1; 
  wjs[2] = tau[1] * wj2; 
  wjs[3] = tau[1] * wj3;
  
  for (i = m+2; i <= 2*m; i++)
  {
    A[i] = A[i] - A[i-m] * wjs[1];
    A[i+m] = A[i+m] - A[i-m] * wjs[2];
    A[i+2*m] = A[i+2*m] - A[i-m] * wjs[3];
  }

  xnorm = aro_eml_sub2norm(A, m+3, 2*m); 
  alphr = A[m+2];
  beta = get_beta(alphr, xnorm); 
  betas[2] = beta;
  tau[2] = (betas[2] - alphr) / betas[2]; 
  alphas[2] = (float)(1.0) / (alphr - betas[2]);
  wj1 = A[2*m+2]; 
  wj2 = A[3*m+2];
  
  for (i = m+3; i <= 2*m; i++)
  {
    A[i] = A[i] * alphas[2];
    wj1 = wj1 + A[i] * A[i+m];
    wj2 = wj2 + A[i] * A[i+2*m];
  }
  wjs[4] = tau[2] * wj1; 
  wjs[5] = tau[2] * wj2;
  
  for (i = 2*m+3; i <= 3*m; i++)
  {
    A[i] = A[i] - A[i-m] * wjs[4];
    A[i+m] = A[i+m] - A[i-m] * wjs[5];
  }
  
  xnorm = aro_eml_sub2norm(A, 2*m+4, 3*m); 
  alphr = A[2*m+3];
  beta = get_beta(alphr, xnorm); 
  betas[3] = beta;
  tau[3] = (betas[3] - alphr) / betas[3]; 
  alphas[3] = (float)(1.0) / (alphr - betas[3]);
  wj1 = A[3*m+3];
  
  for (i = 2*m+4; i <= 3*m; i++)
  {
    A[i] *= alphas[3];
    wj1 = wj1 + A[i] * A[i+m];
  }
  wjs[6] = tau[3] * wj1;
  
  for (i = 3*m+4; i <= 4*m; i++)
    A[i] = (A[i] - A[i-m] * wjs[6]);

  xnorm = aro_eml_sub2norm(A, 3*m+5, 4*m); 
  alphr = A[3*m+4];
  beta = get_beta(alphr, xnorm); 
  betas[4] = beta;
  tau[4] = (betas[4] - alphr) / betas[4]; 
  alphas[4] = (float)(1.0) / (alphr - betas[4]);
  
  for (i = 3*m+5; i <= 4*m; i++)
    A[i] = A[i] * alphas[4];
	
  A[1] = betas[1]; 
  A[m+2] = betas[2]; 
  A[2*m+3] = betas[3]; 
  A[3*m+4] = betas[4];
  A[m+1] = A[m+1] - wjs[1]; 
  A[2*m+1] = A[2*m+1] - wjs[2]; 
  A[3*m+1] = A[3*m+1] - wjs[3];
  A[2*m+2] = A[2*m+2] - wjs[4]; 
  A[3*m+2] = A[3*m+2] - wjs[5];
  A[3*m+3] = A[3*m+3] - wjs[6];
  
  R[1] = A[1]; 
  R[2] = (float)(0.0); 
  R[3] = (float)(0.0); 
  R[4] = (float)(0.0);
  R[5] = A[m+1]; 
  R[6] = A[m+2]; 
  R[7] = (float)(0.0); 
  R[8] = (float)(0.0);
  R[9] = A[2*m+1]; 
  R[10] = A[2*m+2]; 
  R[11] = A[2*m+3]; 
  R[12] = (float)(0.0);
  R[13] = A[3*m+1]; 
  R[14] = A[3*m+2]; 
  R[15] = A[3*m+3]; 
  R[16] = A[3*m+4];

  wj4 = (float)(0.0);
  
  for (i = 3*m+5; i <= 4*m; i++)
  {
    A[i] = -A[i] * tau[4];
    wj4 += (A[i] * A[i-m]);
  }
  
  A[3*m+4] = (float)(1.0) - tau[4]; 
  A[3*m+1] = (float)(0.0);
  A[3*m+2] = (float)(0.0); 
  A[3*m+3] = (float)(0.0);
  wj4 = tau[3] * (wj4 + A[3*m+4] * A[2*m+4]);
  
  if (wj4 != (float)(0.0))
  {
    A[3*m+3] = A[3*m+3] - wj4;
    for (i = 3*m+4; i <= 4*m; i++)
      A[i] = A[i] - A[i-m] * wj4;
  }

  wj1 = (float)(0.0); 
  wj2 = (float)(0.0);
  
  for (i = 2*m+4; i <= 3*m; i++)
  {
    A[i] = -A[i] * tau[3];
    wj1 = wj1 + A[i] * A[i-m];
    wj2 = wj2 + A[i+m] * A[i-m];
  }
  A[2*m+3] = (float)(1.0) - tau[3]; 
  A[2*m+2] = (float)(0.0); 
  A[2*m+1] = (float)(0.0);
  
  wj1 = tau[2] * (wj1 + A[2*m+3] * A[m+3]);
  wj2 = tau[2] * (wj2 + A[3*m+3] * A[m+3]);
  
  if (wj1 != (float)(0.0))
    A[2*m+2] = A[2*m+2] - wj1;

  if (wj2 != (float)(0.0))
    A[3*m+2] = A[3*m+2] - wj2;
	
  for (i = 2*m+3; i <= 3*m; i++)
  {
    if (wj1 != (float)(0.0))
      A[i] -= A[i-m] * wj1;

    if (wj2 != (float)(0.0))
      A[i+m] = A[i+m] - A[i-m] * wj2;
  }

  wj1 = (float)(0.0); 
  wj2 = (float)(0.0); 
  wj3 = (float)(0.0);
  
  for (i = m+3; i <= 2*m; i++)
  {
    A[i] = -A[i] * tau[2];
    wj1 += A[i] * A[i-m];
    wj2 += A[i+m] * A[i-m];
    wj3 += A[i+2*m] * A[i-m];
  }
  
  A[m+2] = (float)(1.0) - tau[2]; 
  A[m+1] = (float)(0.0);
  wj1 = tau[1] * (wj1 + A[m+2] * A[2]);
  wj2 = tau[1] * (wj2 + A[2*m+2] * A[2]);
  wj3 = tau[1] * (wj3 + A[3*m+2] * A[2]);
  
  if (wj1 != (float)(0.0))
    A[m+1] = A[m+1] - wj1;
  
  if (wj2 != (float)(0.0))
    A[2*m+1] = A[2*m+1] - wj2;

  if (wj3 != (float)(0.0))
    A[3*m+1] = A[3*m+1] - wj3;

  for (i = m+2; i <= 2*m; i++)
  {
    if (wj1 != (float)(0.0))
      A[i] = A[i] - A[i-m] * wj1;
    if (wj2 != (float)(0.0))
      A[i+m] = A[i+m] - A[i-m] * wj2;
    if (wj3 != (float)(0.0))
      A[i+2*m] = A[i+2*m] - A[i-m] * wj3;
  }

  for (i = 2; i <= m; i++)
    A[i] = -A[i] * tau[1];

  A[1] = (float)(1.0) - tau[1];

  detR = R[1] * R[6] * R[11] * R[16];
  a11 = R[6] * R[11] * R[16] / detR; 
  a21 = R[5] * R[11] * R[16] / detR; 
  a22 = R[1] * R[11] * R[16] / detR;
  a31 = (R[5] * R[10] * R[16] - R[6]  *R[9] * R[16]) / detR;
  a32 = R[1] * R[10] * R[16] / detR; 
  a33 = R[1] * R[6] * R[16] / detR;
  a41 = (R[5] * R[10] * R[15] + R[6] * R[11] * R[13] - R[5] * R[11] * R[14] - R[6] * R[9] * R[15]) / detR;
  a42 = (R[1] * R[10] * R[15] - R[1] * R[11] * R[14]) / detR;
  a43 = R[1] * R[6] * R[15] / detR; 
  a44 = R[1] * R[6] * R[11] / detR;
  R[1] = a11; 
  R[2] = 0; 
  R[3] = 0; 
  R[4] = 0;
  R[5] = -a21; 
  R[6] = a22; 
  R[7] = 0; 
  R[8] = 0;
  R[9] = a31; 
  R[10] = -a32; 
  R[11] = a33; 
  R[12] = 0;
  R[13] = -a41; 
  R[14] = a42; 
  R[15] = -a43; 
  R[16] = a44;
  
  a41 = (float)(0.0); 
  a42 = (float)(0.0); 
  a43 = (float)(0.0); 
  a44 = (float)(0.0);
  
  for (i = 1; i <= m; i++)
  {
    a41 += A[i] * (float)(y[xstart+i-1+off_y].Data.uint8);
    a42 += A[i+m] * (float)(y[xstart+i-1+off_y].Data.uint8);
    a43 += A[i+2*m] * (float)(y[xstart+i-1+off_y].Data.uint8);
    a44 += A[i+3*m] * (float)(y[xstart+i-1+off_y].Data.uint8);
  }
  
  *c1 = R[1] * a41 + R[5] * a42 + R[9] * a43 + R[13] * a44;
  *c2 = R[2] * a41 + R[6] * a42 + R[10] * a43 + R[14] * a44;
  *c3 = R[3] * a41 + R[7] * a42 + R[11] * a43 + R[15] * a44;
  *c4 = R[4] * a41 + R[8] * a42 + R[12] * a43 + R[16] * a44;
 */
}
