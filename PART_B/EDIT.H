/*======================================
TEditDialog INTERFACE

By Simon Mitchell (96878291)

BASE CLASSES: TDialog
======================================*/

#include <owl/dialog.h>
#include <owl/scrollba.h>
#include <owl/edit.h>
#include <owl/uihelper.h>

#include "part_b.h"
#include "resourc2.rh"

#ifndef EDIT_BIOMORPH_DIALOG
#define EDIT_BIOMORPH_DIALOG

class TEditDialog : public TDialog
{
  public:

    TEditDialog(Interface *, TResId, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, int&, bool);
    ~TEditDialog();
    void Paint(TDC&, bool, TRect);
    void SetupWindow();
    void CloseWindow(){TDialog::CloseWindow();};

  protected:

    // Methods to handle SINGLE UNIT addition to a gene

    void APlus();
    void BPlus();
    void CPlus();
    void DPlus();
    void EPlus();
    void FPlus();
    void GPlus();
    void HPlus();
    void IPlus();
    void JPlus();
    void KPlus();

    // Methods to handle SINGLE UNIT subtraction from a gene

    void AMinus();
    void BMinus();
    void CMinus();
    void DMinus();
    void EMinus();
    void FMinus();
    void GMinus();
    void HMinus();
    void IMinus();
    void JMinus();
    void KMinus();

    // Methods to handle 10 UNIT addition to a gene

    void CCPlus();
    void DDPlus();
    void EEPlus();
    void FFPlus();
    void GGPlus();
    void HHPlus();
    void IIPlus();
    void JJPlus();
    void KKPlus();

    // Methods to handle 10 UNIT subtraction from a gene

    void CCMinus();
    void DDMinus();
    void EEMinus();
    void FFMinus();
    void GGMinus();
    void HHMinus();
    void IIMinus();
    void JJMinus();
    void KKMinus();

    // Misc methods

    void ChangeParent();
    void Draw(bool);
    void Reset();
    void ZeroValues();

    // Methods to keep the edit boxes disabled

    void CeAVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeBVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeCVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeDVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeEVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeFVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeGVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeHVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeIVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeJVal(TCommandEnabler &ce){ce.Enable(false);};
    void CeKVal(TCommandEnabler &ce){ce.Enable(false);};

    // Disable the color adjust buttons if the "colors"
    // flag is not set.

    void CeIPlus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeIMinus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeIIPlus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeIIMinus(TCommandEnabler &ce){ce.Enable(useColors);};

    void CeJPlus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeJMinus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeJJPlus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeJJMinus(TCommandEnabler &ce){ce.Enable(useColors);};

    void CeKPlus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeKMinus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeKKPlus(TCommandEnabler &ce){ce.Enable(useColors);};
    void CeKKMinus(TCommandEnabler &ce){ce.Enable(useColors);};

    void SetValues();
    void CopyToEdit(TEdit*, char *);

    // Point to the parent class

    Interface *myParent;

    // The original gene values

    int oa, ob, oc, od, oe, of, og, oh, oi, oj, ok;

    // Interface elements

    TButton *ok_, *cancel, *reset, *zeroValues;
    TButton *aplus, *bplus, *cplus, *dplus, *eplus, *fplus, *gplus, *hplus,
            *aminus,*bminus,*cminus,*dminus,*eminus,*fminus,*gminus,*hminus,
            *ccplus, *ddplus, *eeplus, *ffplus, *ggplus, *hhplus,
            *ccminus,*ddminus,*eeminus,*ffminus,*ggminus,*hhminus,
            *iiminus, *jjminus, *kkminus, *iiplus, *jjplus, *kkplus,
            *iminus, *jminus, *kminus, *iplus, *jplus, *kplus;

    TEdit *aNum, *bNum, *cNum, *dNum, *eNum, *fNum, *gNum, *hNum, *iNum, *jNum, *kNum;
    TStatic *parentBox;
    TBiomorph *editMorph;

    TStatic *aDes, *bDes, *cDes, *dDes, *eDes, *fDes, *gDes, *hDes, *iDes, *jDes, *kDes;

    bool useColors;

    bool changed;

  DECLARE_RESPONSE_TABLE(TEditDialog);
};

#endif