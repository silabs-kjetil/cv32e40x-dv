#ifndef _COMPLIANCE_MODEL_H
#define _COMPLIANCE_MODEL_H

#define CV_VP_REGISTER_BASE          0x00800000
#define CV_VP_STATUS_FLAGS_OFFSET    0x000000c0

#define RVMODEL_DATA_SECTION                        \
  .align 8; .global begin_regstate; begin_regstate: \
  .word 128;                                        \
  .align 8; .global end_regstate; end_regstate:     \
  .word 4;

//RV_COMPLIANCE_HALT
#define RVMODEL_HALT                        \
  li x1, 123456789;                         \
  li t5, CV_VP_REGISTER_BASE;               \
write_status:                               \
    sw x1, CV_VP_STATUS_FLAGS_OFFSET(t5);   \
    j write_status;

#define RVMODEL_BOOT                        \
  csrw    mtvec, x0;                        \
  la    t3, begin_signature;                \
  sw    t3, __TEST_SIG_BEGIN_ADDR, t4;      \
  la    t3, end_signature;                  \
  sw    t3, __TEST_SIG_END_ADDR, t4;

//RV_COMPLIANCE_DATA_BEGIN
#define RVMODEL_DATA_BEGIN                  \
  RVMODEL_DATA_SECTION                      \
  .align 4;                                 \
  .global begin_signature; begin_signature:

//RV_COMPLIANCE_DATA_END
#define RVMODEL_DATA_END                    \
  .align 4;                                 \
  .global end_signature; end_signature:  

//RVTEST_IO_INIT
#define RVMODEL_IO_INIT
//RVTEST_IO_WRITE_STR
#define RVMODEL_IO_WRITE_STR(_R, _STR)
//RVTEST_IO_CHECK
#define RVMODEL_IO_CHECK()
//RVTEST_IO_ASSERT_GPR_EQ
#define RVMODEL_IO_ASSERT_GPR_EQ(_S, _R, _I)
//RVTEST_IO_ASSERT_SFPR_EQ
#define RVMODEL_IO_ASSERT_SFPR_EQ(_F, _R, _I)
//RVTEST_IO_ASSERT_DFPR_EQ
#define RVMODEL_IO_ASSERT_DFPR_EQ(_D, _R, _I)

#define RVMODEL_SET_MSW_INT

#define RVMODEL_CLEAR_MSW_INT

#define RVMODEL_CLEAR_MTIMER_INT

#define RVMODEL_CLEAR_MEXT_INT

#define SET_REL_TVAL_MSK 0x00000000

#define RVMODEL_MTVEC_ALIGN 8

#endif // _COMPLIANCE_MODEL_H
