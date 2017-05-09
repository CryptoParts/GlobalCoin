#ifndef MESSAGES_H
#define MESSAGES_H

#include "bitcoinrpc.h"
#include "checkpoints.h"
#include "db.h"
#include "init.h"
#include "main.h"
#include "net.h"
#include "util.h"
#include "ui_interface.h"


bool AlreadyHave(CTxDB& txdb, const CInv& inv);
bool ProcessMessages(CNode* pfrom);
bool SendMessages(CNode* pto, bool fSendTrickle);


#endif // MESSAGES_H
