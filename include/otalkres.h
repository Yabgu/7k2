/*
 * Seven Kingdoms 2: The Fryhtan War
 *
 * Copyright 1999 Enlight Software Ltd.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

// Filename	  : OTALKRES.H
// Description : Header file for class TalkRes

#ifndef __OTALKRES_H
#define __OTALKRES_H

#ifndef __OSTR_H
#include <ostr.h>
#endif

#ifndef __ODYNARRB_H
#include <odynarrb.h>
#endif

#ifndef __OTALKMSG_H
#include <otalkmsg.h>
#endif

//-------- define constant ----------//

enum
{
    MAX_TALK_CHOICE = 10
}; // maximum talk lines can be displayed in the area

enum
{
    MAX_WAIT_MSG_PER_NATION = 3
}; // you cannot send more than 3 messages to a nation until it processes some
   // of them

enum
{
    TALK_MSG_KEEP_DAYS = 365
}; // keep TalkMsg for 365 days before deleteing it.

//-------- define reply answer ------//

enum
{
    REPLY_NOT_NEEDED, // do not need a reply for this messge, it's a informing
                      // message only
    REPLY_WAITING,
    REPLY_ACCEPT,
    REPLY_REJECT
};

//------- Define struct TalkMsg -------//

#pragma pack(1)
struct TalkMsg
{
  public:
    short talk_id;
    short talk_para1;
    short talk_para2;
    short talk_para3;
    short talk_para4;

    int date;

    char from_nation_recno;
    char to_nation_recno;
    char from_nation_invisible; // 1 if from_nation_recno cannot see this message
                                // (create incident)

    char reply_type; // whether this is a reply message.
    int reply_date;

    char relation_status; // the relation status of the two nations when the
                          // message is sent

    //-----------------------------------//

    char *from_nation_name();
    char *to_nation_name();

    char *from_king_name();
    char *to_king_name();

    char *third_nation_name(int nationRecno);

    char *nation_color_code_str(int nationRecno);

    //-----------------------------------//

  public:
    TalkMsg();

    char *msg_str(int viewingNationRecno, int dispReply = 1, int dispSecondLine = 0);

    int is_reply_needed(); // whether a reply is needed for this message
    int is_valid_to_disp();
    int is_valid_to_reply();
    int can_accept();

    void process_accepted_reply();

    void propose_treaty(const char *);
    void end_treaty(const char *);
    void request_military_aid();
    void request_trade_embargo();
    void request_cease_war();
    void request_declare_war();
    void request_buy_food();
    void declare_war();
    void give_tribute(const char *tributeStr);
    void demand_tribute(int isAid);
    void exchange_tech();
    void request_surrender();
    void surrender();

    // ###### begin Gilbert 10/10 #########//
    UCHAR crc8();
    void clear_ptr();
    // ###### end Gilbert 10/10 #########//
};
#pragma pack()

//------- Define struct TalkChoice -------//

#pragma pack(1)
struct TalkChoice
{
    enum
    {
        CHOICE_TEXT_LEN = 100
    };

    char str[CHOICE_TEXT_LEN + 1];
    short para;
    short para2;
};
#pragma pack()

//------ Define class TalkRes --------//

#pragma pack(1)
class TalkRes
{
  public:
    char init_flag;

    short reply_talk_msg_recno;

    TalkMsg cur_talk_msg;
    char *choice_question;
    char *choice_question_second_line;

    short talk_choice_count;
    TalkChoice talk_choice_array[MAX_TALK_CHOICE];

    char available_talk_id_array[MAX_TALK_TYPE];

    short cur_choice_id;
    char save_view_mode;

    char msg_add_nation_color;

    DynArrayB talk_msg_array;

  public:
    TalkRes();

    void init();
    void deinit();

    void init_conversion(int nationRecno);

    void disp_talk();
    int detect_talk();

    int ai_send_talk_msg(int toNationRecno, int fromNationRecno, int talkId, int talkPara1 = 0, int talkPara2 = 0,
                         int forceSend = 0, int talkPara3 = 0, int talkPara4 = 0);
    void send_talk_msg(TalkMsg *, char remoteAction, int forceSend = 0);
    void send_talk_msg_now(TalkMsg *);
    void reply_talk_msg(int talkMsgRecno, char replyType, char remoteAction);
    int can_send_msg(int toNationRecno, int fromNationRecno, int talkId);
    int can_send_any_msg(int toNationRecno, int fromNationRecno);
    // ##### begin Gilbert 11/12 #######//
    void create_incident(int nation1, int nation2);
    // ##### end Gilbert 11/12 #######//

    int set_talk_choices();
    void player_reply(int talkMsgRecno);

    int talk_msg_count()
    {
        return talk_msg_array.size();
    }
    int wait_msg_count(int toNationRecno, int fromNationRecno);

    TalkMsg *get_talk_msg(int recNo);
    void del_talk_msg(int recNo);
    int is_talk_msg_deleted(int recNo);
    void del_all_nation_msg(int nationRecno);

    int is_talk_msg_exist(TalkMsg *thisTalkMsg, int checkPara);

    void next_day();

    int write_file(File *filePtr);
    int read_file(File *filePtr);

  private:
    void add_talk_choice(const char *talkStr, int talkPara, int talkPara2 = 0);

    void add_main_choices();
    int add_trade_embargo_choices();
    int add_declare_war_choices();
    int add_buy_food_choices();
    int add_tribute_choices();
    int add_exchange_tech_choices();
    int add_surrender_choices();
    int add_request_surrender_choices();

    int detect_talk_choices();

    void process_talk_msg();
};
#pragma pack()

extern TalkRes talk_res;

//------------------------------------//

#endif
