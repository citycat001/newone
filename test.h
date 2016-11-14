//+------------------------------------------------------------------+
//|                                                         test.mqh |
//|                        Copyright 2016, MetaQuotes Software Corp. |
//|                                             https://www.mql5.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2016, MetaQuotes Software Corp."
#property link      "https://www.mql5.com"
#property strict
//+------------------------------------------------------------------+
//| defines                                                          |
//+------------------------------------------------------------------+
#define STATUS_OBJARR_SIZE                                6
#define GRADIENT_THRESHOLD_UP                             0.2
#define GRADIENT_THRESHOLD_DOWN                           -0.2
#define GRADIENT_THRESHOLD_UP_INFINIT                     90.0
#define GRADIENT_THRESHOLD_DOWN_INFINIT                   -90.0
#define GRADIENT_THRESHOLD_CHANGE_UP                      0.8   
#define GRADIENT_THRESHOLD_CHANGE_DOWN                    -0.8 
#define GRADIENT_THRESHOLD_CHANGE_UP_CUR                  1.2   
#define GRADIENT_THRESHOLD_CHANGE_DOWN_CUR                -1.2
#define INDICATOR_COUNT                                   5          //including MACD_history, MACD_2color, ADX, EMA, BB Band
//#define EINDICATORSTATUS_COUNT                            8          //number of the enum value in EINDICATORSTATUS
#define BBBAND_THRESHOD                                   20         //upper price minus lower price, if less than 20, means price space is not hight, better not trade.

//custom error code
#define ERROR_VALUEASSIGN                                 -1
#define ERROR_MULTORDER                                   -2

//+------------------------------------------------------------------+
//| DLL imports                                                      |
//+------------------------------------------------------------------+
// #import "user32.dll"
//   int      SendMessageA(int hWnd,int Msg,int wParam,int lParam);
// #import "my_expert.dll"
//   int      ExpertRecalculate(int wParam,int lParam);
// #import
//+------------------------------------------------------------------+
//| EX5 imports                                                      |
//+------------------------------------------------------------------+
// #import "stdlib.ex5"
//   string ErrorDescription(int error_code);
// #import
//+------------------------------------------------------------------+

enum ESHIFT
{
   SHIFT_CURRENT = 0,
   SHIFT_LAST_ONE = 1,
   SHIFT_LAST_TWO = 2,
   SHIFT_LAST_THRID = 3,
};

enum ETIMERANGE
{
   TIMERANGE_NO = 0,
   TIMERANGE_EU = 1,
   TIMERANGE_US = 2,
};

enum ECCISTATUS
{
   STATUS_CCI_LONG = 1,
   STATUS_CCI_SHORT = 2,
};

enum EMACD2CSTATUS
{
   STATUS_MACD2C_V1_UP = 1,
   STATUS_MACD2C_V1_DOWN = 2,
   STATUS_MACD2C_ABOVE_YL = 3,
   STATUS_MACD2C_BELOW_YL = 4,
};

enum EMACD2CMODE
{
   MODE_MACD2C_BL = 0,
   MODE_MACD2C_WAVE = 1,
   MODE_MACD2C_POSITIVE = 2,
   MODE_MACD2C_NEGATIVE = 3,
};

enum EINDICATORSTATUS
{
   STATUS_CROSS_UP = 1,
   STATUS_CROSS_DOWN = 2,
   STATUS_KEEP_UP = 3,
   STATUS_KEEP_DOWN = 4,
   STATUS_BAD = 5,   
   STATUS_CLOSE = 6,
   STATUS_UNKNOWN = 7,
//   STATUS_GOOD_BBBAND = 8,
};

enum ELINERELATION
{
   LINERELATION_UNKNOWN = 0,
   LINERELATION_CROSSUP = 1,
   LINERELATION_CROSSDOWN = 2,
   LINERELATION_UPCLOSE = 3,
   LINERELATION_UPOPEN = 4,
   LINERELATION_DOWNCLOSE = 5,
   LINERELATION_DOWNOPEN = 6,
};

enum EORDERINS
{
   ORDER_OPEN_BUY = 1,
   ORDER_KEEP = 2,
   ORDER_CLOSE = 3,
   ORDER_OPEN_SELL = 4,
   ORDER_NO = 0,
};

enum EARRAYINDEXINDICATOR
{
   ARRAYINDEX_ADX = 0,
   ARRAYINDEX_MACDH = 1,
   ARRAYINDEX_MACD2C = 2,
   ARRAYINDEX_EMA = 3,
   ARRAYINDEX_BBBAND = 4,
};

enum EARRAYINDEXPERIOD
{
   ARRAYINDEX_H4 = 0,
   ARRAYINDEX_H1 = 1,
   ARRAYINDEX_M30 = 2,
   ARRAYINDEX_M15 = 3,
   ARRAYINDEX_M5 = 4,
   ARRAYINDEX_M3 = 5,
};

class CStatus
{
protected:
   int m_timeframe;
   string m_symb;
   int m_period;
   int m_apprice;
   int m_bb_deviation;
   int m_bbperiod;
public:
   virtual bool AssignValueSM(int& smatrix[][], int indicator, int status);
   virtual int CheckADX(int& smatrix[][]);
   //gradient parameters are to indicate the difference of gradient of MACDH fast line. To determine the speed of the change of fast line
   virtual int CheckMACDH(int& smatrix[][], double& gradient_sec, double& gradient_old, double& gradient_cur); 
   virtual int CheckEMA(int& smatrix[][]);
   virtual int CheckBollinger(int& smatrix[][]);
   virtual int CheckMACD2C(int& smatrix[][]){return 0;};
   virtual int GetLineRelation(double c1, double c2, double l1, double l2, double ll1, double ll2, int time_frame);
   virtual int CalculateGradient(double gradient_old, double gradient_cur);
};

class CStatusH4 : public CStatus
{
public:
   CStatusH4(string s);
};

class CStatusH1 : public CStatus
{
public:
   CStatusH1(string s);
};

class CStatusM30 : public CStatus
{
public:
   CStatusM30(string s);
};

class CStatusM15 : public CStatus
{
public:
   CStatusM15(string s);
};

class CStatusM5 : public CStatus
{
public:
   CStatusM5(string s);
};

class CStatusM3 : public CStatus
{
public:
   CStatusM3(string s);
};


//M5V1 trading system
class CStatusV1M30 : public CStatus
{
public:
   CStatusV1M30(string s);
   virtual int CheckADX(int& smatrix[][]);
};

class CStatusV1M15 : public CStatus
{
public:
   CStatusV1M15(string s);
   virtual int CheckADX(int& smatrix[][]);
   virtual int CheckMACD2C(int& smatrix[][]);
};

class CStatusV1M5 : public CStatus
{
public:
   CStatusV1M5(string s);
   virtual int CheckADX(int& smatrix[][]);
   virtual int CheckMACD2C(int& smatrix[][]);
};
