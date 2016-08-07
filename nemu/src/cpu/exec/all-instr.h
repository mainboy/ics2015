#include "prefix/prefix.h"

#include "data-mov/mov.h"
#include "data-mov/xchg.h"
#include "data-mov/push.h"
#include "data-mov/leave.h"
#include "data-mov/pop.h"
#include "data-mov/movzx.h"

#include "arith/dec.h"
#include "arith/inc.h"
#include "arith/neg.h"
#include "arith/imul.h"
#include "arith/mul.h"
#include "arith/idiv.h"
#include "arith/div.h"
#include "arith/sub.h"
#include "arith/cmp.h"
#include "arith/add.h"
#include "arith/adc.h"

#include "logic/and.h"
#include "logic/or.h"
#include "logic/not.h"
#include "logic/xor.h"
#include "logic/sar.h"
#include "logic/shl.h"
#include "logic/shr.h"
#include "logic/shrd.h"
#include "logic/test.h"

#include "string/rep.h"

#include "misc/misc.h"
#include "misc/lea.h"

#include "special/special.h"

#include "ctl-transfer/call.h"
#include "ctl-transfer/je.h"
#include "ctl-transfer/jmp.h"
#include "ctl-transfer/jbe.h"
#include "ctl-transfer/ret.h"

