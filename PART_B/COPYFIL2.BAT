cls
@echo off

a:
cd\
mkdir part_b
c:

echo "COPYING PART_B FILES ..."
copy part_b.cpp a:\part_b
copy part_b.h a:\part_b
copy part_b.ide a:\part_b
copy part_b.exe a:\part_b

echo "COPYING ANIMATION STRUCT FILES ..."
copy animstruc.h a:\part_b

echo "COPYING RESOURCE SCRIPT ..."
copy part_b.rc a:\part_b

echo "COPYING RESOURCE HEADER ..."
copy resourc2.rh a:\part_b

echo "COPYING BIOMORPH FILES ..."
copy biomorph.h a:\part_b
copy biomorph.cpp a:\part_b

echo "COPYING EDIT DIALOG FILES ..."
copy edit.h a:\part_b
copy edit.cpp a:\part_b

echo "COPYING STATISTICS DIALOG FILES ..."
copy stats.h a:\part_b
copy stats.cpp a:\part_b

echo "COPYING GENE VALUE DIALOG FILES ..."
copy genes.h a:\part_b
copy genes.cpp a:\part_b

echo "COPYING MANAGER FILES ..."
copy manager.h a:\part_b
copy manager.cpp a:\part_b

echo "COPYING ARRAY ADS FILES ..."
copy array.h a:\part_b
copy array.cpp a:\part_b

echo "COPYING OFFSPRING COUNT DIALOG FILES ..."
copy offsprin.h a:\part_b
copy offsprin.cpp a:\part_b

echo "COPYING BIO_VIEW FILES ..."
copy bio_view.exe a:\part_b
copy bio_view.cpp a:\part_b
copy bio_view.h a:\part_b
copy bio_view.ide a:\part_b

echo "COPYING ANIMATOR FILES ..."
copy animator.exe a:\part_b
copy animator.cpp a:\part_b
copy animator.ide a:\part_b
copy animator.rh a:\part_b

echo "*** COPYING COMPLETE! ***"

