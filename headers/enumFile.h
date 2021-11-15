enum ePrimaryMenu {
    PRIMARY_MENU_EXIT,
    PRIMARY_MENU_PROGRAMMER,
    PRIMARY_MENU_TESTER

};

enum StatusOfReport
{
    NEW = 1,
    FIXED,
    CLOSED
};

enum bugReportStructPos
{
    UNIQUE_ID_POS,
    SHORT_DESC_POS,  // POS 1
    DESC_POS,
    DATE_CREATION_POS,
    DATE_FIXED_POS,  // POS 4
    DATE_CLOSED_POS, // POS 5
    TESTER_POS,
    PROGRAMMER_POS,
    STATUS_REPORT_POS // POS 8
};

enum eUserType
{
    PROGRAMMER = 1,
    TESTER,
    GUEST
};

typedef enum eUserType enUserType;

enum loginDetailsStructPos
{
    USERNAME,
    PASSWORD,
    USERTYPE
};

enum eBoolean
{
    false,
    true
};

enum ePrintType
{
    NEW_TYPE,
    FIXED_TYPE,
    CLOSED_TYPE,
    REGULAR_TYPE,
    REVERSED_TYPE
};

typedef enum ePrintType enPrintType;

enum ePrintLines {
    oneLine = 1,
    twoLines,
    threeLines,
    fourLines
};