$yysccsid = "@(#)yaccpar 1.8 (Berkeley) 01/20/91 (Python 2.0 12/31/92)";
#define YYBYACC 1
INT=257
FLOAT=258
STRING=259
IDENT=260
EQ=261
NE=262
GT=263
GE=264
LT=265
LE=266
L_SHIFT=267
R_SHIFT=268
EXP=269
UNARY=270
YYERRCODE=256
yylhs = [                                               -1,
    0,    0,    1,    1,    1,    2,    2,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,
]
yylen = [                                                2,
    0,    2,    1,    2,    2,    1,    1,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    2,    2,    2,    2,    2,    3,    1,
    1,    1,    1,    1,
]
yydefred = [                                             1,
    0,    0,   31,   32,   33,    0,    0,    0,    0,    0,
    6,    7,    0,   34,    2,    3,    0,    5,    0,   28,
   27,   25,   26,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   24,
    4,    0,    8,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,
]
yydgoto = [                                              1,
   15,   16,   17,
]
yysindex = [                                             0,
  147,   30,    0,    0,    0,  -60, -257,  375,  375,  375,
    0,    0,  375,    0,    0,    0,    1,    0,  375,    0,
    0,    0,    0,  -28,  375,  375,  375,  375,  375,  375,
  375,  375,  375,  375,  375,  375,  375,  375,  375,    0,
    0,  166,    0,  130,  183,  301,  301,  109,  109,  109,
  109,  172,  172,  -26,  -26,  -27,  -27,  -27,
]
yyrindex = [                                             0,
    0,    0,    0,    0,    0,  -10,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   41,    0,  190,   78,  120,  124,   88,   94,  100,
  108,   65,   74,   42,   54,   12,   20,   31,
]
yygindex = [                                             0,
    0,    7,  445,
]
YYTABLESIZE=635
yytable = [                                             30,
   19,   20,    0,    0,   40,   40,   40,    0,   18,   26,
   12,    0,   43,   37,   35,   37,   36,    0,   38,    0,
   38,   21,   30,   41,    0,    0,    0,   30,    0,   22,
   30,   30,   30,   40,   30,    0,   30,    0,   26,   12,
   23,    0,   37,   35,    0,   36,    0,   38,   30,   21,
   29,   19,   21,   21,   21,    0,   21,   22,   21,   11,
   22,   22,   22,   20,   22,    0,   22,    0,   23,    0,
   21,   23,   23,   23,   17,   23,    0,   23,   22,   19,
    0,   29,   19,   18,   19,    0,   19,   10,   11,   23,
    0,   20,    0,    0,   20,   25,   20,   13,   20,   29,
   19,    0,   17,   14,    0,   17,    0,    0,    0,   15,
    0,   18,   20,   30,   18,   10,    0,   16,   10,    0,
    0,    0,    0,   17,   25,   13,    0,    0,   13,   11,
    0,   14,   18,   12,   14,   21,   10,   15,    0,    0,
   15,   40,    0,   22,    0,   16,   13,    0,   16,    0,
   37,   35,   14,   36,   23,   38,   12,   11,   15,    0,
   11,   12,   40,    0,   12,   19,   16,   26,    0,    0,
    0,   37,   35,    0,   36,    0,   38,   20,   11,   10,
    0,    0,   12,   14,    7,    0,   13,    0,   17,    8,
    0,    9,    0,    0,    0,    0,    0,   18,   40,    9,
    0,   10,    0,   26,   40,   11,    0,   37,   35,    0,
   36,   13,   38,   37,   35,   40,   36,   14,   38,    0,
    0,    0,    0,   15,   37,   35,    0,   36,    0,   38,
    9,   16,   27,   28,   29,   30,   31,   32,   33,   34,
   39,   39,   39,   11,    0,    0,    0,   12,    9,    0,
   30,   30,   30,   30,   30,   30,   30,   30,   30,    0,
    0,   27,   28,   29,   30,   31,   32,   33,   34,   39,
    0,    0,   21,   21,   21,   21,   21,   21,   21,   21,
   22,   22,   22,   22,   22,   22,   22,   22,    0,   25,
    0,   23,   23,   23,   23,   23,   23,   23,   23,    0,
    0,    0,   19,   19,   19,   19,   19,   19,   19,   19,
    0,    0,    0,    9,   20,   20,   20,   20,   20,   20,
   20,   20,    0,    0,    0,   17,   17,   17,   17,   17,
   17,   17,   17,   40,   18,   18,   18,   18,   18,   18,
   18,   18,   37,   35,    0,   36,    0,   38,   13,   13,
   13,   13,   13,   13,   14,   14,   14,   14,   14,   14,
   15,   15,   15,   15,   15,   15,    0,    0,   16,   16,
   16,   16,   16,   16,    0,   33,   34,   39,    0,    0,
   11,   11,    0,    0,   12,   12,    0,    0,    0,    0,
   27,   28,   29,   30,   31,   32,   33,   34,   39,    0,
    0,    0,    2,    3,    4,    5,    6,   10,    0,    0,
    0,   14,    7,    0,   13,    0,    0,    8,    0,    9,
    0,    0,    0,    0,    0,    0,   27,   28,   29,   30,
   31,   32,   33,   34,   39,    0,    0,    0,    0,    0,
   39,    0,    0,   27,   28,   29,   30,   31,   32,   33,
   34,   39,   21,   22,   23,    0,    0,   24,    0,    0,
    0,    0,    0,   42,    0,    0,    0,    0,    0,   44,
   45,   46,   47,   48,   49,   50,   51,   52,   53,   54,
   55,   56,   57,   58,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   29,   30,   31,   32,   33,   34,   39,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    3,    4,    5,    6,
]
yycheck = [                                             10,
   61,  259,   -1,   -1,   33,   33,   33,   -1,    2,   38,
   10,   -1,   41,   42,   43,   42,   45,   -1,   47,   -1,
   47,   10,   33,   17,   -1,   -1,   -1,   38,   -1,   10,
   41,   42,   43,   33,   45,   -1,   47,   -1,   38,   10,
   10,   -1,   42,   43,   -1,   45,   -1,   47,   59,   38,
   10,   10,   41,   42,   43,   -1,   45,   38,   47,   59,
   41,   42,   43,   10,   45,   -1,   47,   -1,   38,   -1,
   59,   41,   42,   43,   10,   45,   -1,   47,   59,   38,
   -1,   41,   41,   10,   43,   -1,   45,   10,   59,   59,
   -1,   38,   -1,   -1,   41,  124,   43,   10,   45,   59,
   59,   -1,   38,   10,   -1,   41,   -1,   -1,   -1,   10,
   -1,   38,   59,  124,   41,   38,   -1,   10,   41,   -1,
   -1,   -1,   -1,   59,  124,   38,   -1,   -1,   41,   10,
   -1,   38,   59,   10,   41,  124,   59,   38,   -1,   -1,
   41,   33,   -1,  124,   -1,   38,   59,   -1,   41,   -1,
   42,   43,   59,   45,  124,   47,   10,   38,   59,   -1,
   41,   38,   33,   -1,   41,  124,   59,   38,   -1,   -1,
   -1,   42,   43,   -1,   45,   -1,   47,  124,   59,   33,
   -1,   -1,   59,   37,   38,   -1,   40,   -1,  124,   43,
   -1,   45,   -1,   -1,   -1,   -1,   -1,  124,   33,   10,
   -1,  124,   -1,   38,   33,   59,   -1,   42,   43,   -1,
   45,  124,   47,   42,   43,   33,   45,  124,   47,   -1,
   -1,   -1,   -1,  124,   42,   43,   -1,   45,   -1,   47,
   41,  124,  261,  262,  263,  264,  265,  266,  267,  268,
  269,  269,  269,  124,   -1,   -1,   -1,  124,   59,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  269,   -1,
   -1,  261,  262,  263,  264,  265,  266,  267,  268,  269,
   -1,   -1,  261,  262,  263,  264,  265,  266,  267,  268,
  261,  262,  263,  264,  265,  266,  267,  268,   -1,  124,
   -1,  261,  262,  263,  264,  265,  266,  267,  268,   -1,
   -1,   -1,  261,  262,  263,  264,  265,  266,  267,  268,
   -1,   -1,   -1,  124,  261,  262,  263,  264,  265,  266,
  267,  268,   -1,   -1,   -1,  261,  262,  263,  264,  265,
  266,  267,  268,   33,  261,  262,  263,  264,  265,  266,
  267,  268,   42,   43,   -1,   45,   -1,   47,  261,  262,
  263,  264,  265,  266,  261,  262,  263,  264,  265,  266,
  261,  262,  263,  264,  265,  266,   -1,   -1,  261,  262,
  263,  264,  265,  266,   -1,  267,  268,  269,   -1,   -1,
  261,  262,   -1,   -1,  261,  262,   -1,   -1,   -1,   -1,
  261,  262,  263,  264,  265,  266,  267,  268,  269,   -1,
   -1,   -1,  256,  257,  258,  259,  260,   33,   -1,   -1,
   -1,   37,   38,   -1,   40,   -1,   -1,   43,   -1,   45,
   -1,   -1,   -1,   -1,   -1,   -1,  261,  262,  263,  264,
  265,  266,  267,  268,  269,   -1,   -1,   -1,   -1,   -1,
  269,   -1,   -1,  261,  262,  263,  264,  265,  266,  267,
  268,  269,    8,    9,   10,   -1,   -1,   13,   -1,   -1,
   -1,   -1,   -1,   19,   -1,   -1,   -1,   -1,   -1,   25,
   26,   27,   28,   29,   30,   31,   32,   33,   34,   35,
   36,   37,   38,   39,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  263,  264,  265,  266,  267,  268,  269,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  257,  258,  259,  260,
]
YYFINAL=1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
YYMAXTOKEN=270
#if YYDEBUG
yyname = [
"end-of-file",0,0,0,0,0,0,0,0,0,"'\\n'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'!'",0,0,0,"'%'","'&'",0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,
0,0,0,0,0,0,"';'",0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"INT","FLOAT","STRING","IDENT","EQ","NE","GT","GE","LT",
"LE","L_SHIFT","R_SHIFT","EXP","UNARY",
]
yyrule = [
"$accept : stmt_list",
"stmt_list :",
"stmt_list : stmt_list stmt",
"stmt : terminator",
"stmt : expr terminator",
"stmt : error terminator",
"terminator : ';'",
"terminator : '\\n'",
"expr : '(' expr ')'",
"expr : expr '|' expr",
"expr : expr '&' expr",
"expr : expr EQ expr",
"expr : expr NE expr",
"expr : expr GT expr",
"expr : expr GE expr",
"expr : expr LT expr",
"expr : expr LE expr",
"expr : expr L_SHIFT expr",
"expr : expr R_SHIFT expr",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr EXP expr",
"expr : expr '!'",
"expr : '-' expr",
"expr : '!' expr",
"expr : '+' expr",
"expr : '&' STRING",
"expr : IDENT '=' expr",
"expr : IDENT",
"expr : INT",
"expr : FLOAT",
"expr : STRING",
"expr : '%'",
]
#endif
def yyclearin :
    yychar = -1;
def yyerrok :
    yyerrflag = 0;
YYSTACKSIZE = YYSTACKSIZE || YYMAXDEPTH || 500;
YYMAXDEPTH = YYMAXDEPTH || YYSTACKSIZE || 500;
yyss[YYSTACKSIZE] = 0;
yyvs[YYSTACKSIZE] = 0;
def YYERROR :
  ++yynerrs
  yy_err_recover()

def yy_err_recover :
  if yyerrflag < 3 :
    yyerrflag = 3;
    while 1 :
      yyn = yysindex[yyss[yyssp]]
      if yyn :
        yyn += YYERRCODE
        if yyn >= 0 and yycheck[yyn] == YYERRCODE :
        {
          $yyss[++$yyssp] = $yystate = $yytable[$yyn];
          $yyvs[++$yyvsp] = $yylval;
          next yyloop;
        }
        else
        {
          return(1) if $yyssp <= 0;
          --$yyssp;
          --$yyvsp;
        }
  else :
    if yychar == 0 :
      return (1) 
    yychar = -1;
    next yyloop;

  return 0

sub yyparse
{
  yynerrs = 0;
  yyerrflag = 0;
  yychar = (-1);

  yyssp = 0;
  yyvsp = 0;
  yyss[yyssp] = 0;
  yystate = 0;

#yyloop:
while 1 :
  {
    #yyreduce: 
      if yyn = yydefred[yystate] :
        break
      if yychar < 0 :
        yychar = yylex
        if yychar < 0 :
          yychar = 0
      yyn = yysindex[yystate]
      if yyn :
        yyn += yychar
        if yyn >= 0 and yycheck[yyn] == yychar :
          yyss[++yyssp] = yystate = yytable[yyn]
          yyvs[++yyvsp] = yylval
          yychar = (-1)
          if yyerrflag > 0 :
            --yyerrflag 
          continue
      yyn = yyrindex[yystate]
      if yyn :
        yyn += yychar
        if yyn >= 0 and yycheck[yyn] == yychar :
          yyn = yytable[yyn]
          break
      if ! yyerrflag :
        yyerror('syntax error')
        ++yynerrs
      if yy_err_recover() :
        return(1)
    } # yyreduce
    yym = yylen[yyn]
    yyval = yyvs[yyvsp+1-yym]
    # switch:
    {
    if yyn == 4 :
#line 45 "calc.y"
      print yyvs[yyvsp-1], "\n" if yyvs[yyvsp-0] eq "\n"; $P = yyvs[yyvsp-1]; 
    if yyn == 5 :
#line 47 "calc.y"
     &yyerrok; 
    if yyn == 6 :
#line 51 "calc.y"
     yyval = yyvs[yyvsp-0]; 
    if yyn == 7 :
#line 53 "calc.y"
     yyval = yyvs[yyvsp-0]; 
    if yyn == 8 :
#line 57 "calc.y"
     yyval = yyvs[yyvsp-1]; 
    if yyn == 9 :
#line 59 "calc.y"
     yyval = yyvs[yyvsp-2] || yyvs[yyvsp-0]; 
    if yyn == 10 :
#line 61 "calc.y"
     yyval = yyvs[yyvsp-2] && yyvs[yyvsp-0]; 
    if yyn == 11 :
#line 63 "calc.y"
     yyval = yyvs[yyvsp-2] == yyvs[yyvsp-0]; 
    if yyn == 12 :
#line 65 "calc.y"
     yyval = yyvs[yyvsp-2] != yyvs[yyvsp-0]; 
    if yyn == 13 :
#line 67 "calc.y"
     yyval = yyvs[yyvsp-2] > yyvs[yyvsp-0]; 
    if yyn == 14 :
#line 69 "calc.y"
     yyval = yyvs[yyvsp-2] >= yyvs[yyvsp-0]; 
    if yyn == 15 :
#line 71 "calc.y"
     yyval = yyvs[yyvsp-2] < yyvs[yyvsp-0]; 
    if yyn == 16 :
#line 73 "calc.y"
     yyval = yyvs[yyvsp-2] <= yyvs[yyvsp-0]; 
    if yyn == 17 :
#line 75 "calc.y"
     yyval = yyvs[yyvsp-2] << yyvs[yyvsp-0]; 
    if yyn == 18 :
#line 77 "calc.y"
     yyval = yyvs[yyvsp-2] >> yyvs[yyvsp-0]; 
    if yyn == 19 :
#line 79 "calc.y"
     yyval = yyvs[yyvsp-2] + yyvs[yyvsp-0]; 
    if yyn == 20 :
#line 81 "calc.y"
     yyval = yyvs[yyvsp-2] - yyvs[yyvsp-0]; 
    if yyn == 21 :
#line 83 "calc.y"
     yyval = yyvs[yyvsp-2] * yyvs[yyvsp-0]; 
    if yyn == 22 :
#line 85 "calc.y"
     yyval = yyvs[yyvsp-2] / yyvs[yyvsp-0]; 
    if yyn == 23 :
#line 87 "calc.y"
     yyval = yyvs[yyvsp-2] ** yyvs[yyvsp-0]; 
    if yyn == 24 :
#line 89 "calc.y"
     yyval = &fact(yyvs[yyvsp-1]); 
    if yyn == 25 :
#line 91 "calc.y"
     yyval = -yyvs[yyvsp-0]; 
    if yyn == 26 :
#line 93 "calc.y"
     yyval = !yyvs[yyvsp-0]; 
    if yyn == 27 :
#line 95 "calc.y"
     yyval = yyvs[yyvsp-0]; 
    if yyn == 28 :
#line 97 "calc.y"
     yyval = eval(yyvs[yyvsp-0]); 
    if yyn == 29 :
#line 99 "calc.y"
     eval '$V{'.yyvs[yyvsp-2].'}=('.yyvs[yyvsp-0].'); 1' || &yyerror($@); yyval = $Vyyvs[yyvsp-2]}; 
    if yyn == 30 :
#line 101 "calc.y"
     if (! defined $Vyyvs[yyvsp-0]}) 
		    &yyerror(yyvs[yyvsp-0].": undefined variable");
		    $Vyyvs[yyvsp-0]} = 0;
		  }
		  yyval = $Vyyvs[yyvsp-0]};
		
    if yyn == 31 :
#line 108 "calc.y"
     yyval = yyvs[yyvsp-0]; 
    if yyn == 32 :
#line 110 "calc.y"
     yyval = yyvs[yyvsp-0]; 
    if yyn == 33 :
#line 112 "calc.y"
     yyval = yyvs[yyvsp-0]; 
    if yyn == 34 :
#line 114 "calc.y"
     yyval = $P; 
#line 471 "y.tab.py"
    } # switch
    yyssp -= yym;
    yystate = yyss[yyssp];
    yyvsp -= yym;
    yym = yylhs[yyn];
    if yystate == 0 and yym == 0 :
      yystate = YYFINAL;
      yyss[++yyssp] = YYFINAL;
      yyvs[++yyvsp] = yyval;
      if (yychar < 0)
        yychar = yylex()
        if yychar < 0 :
          yychar = 0
      if yychar :
        return(0)
      continue

    if (($yyn = $yygindex[$yym]) && ($yyn += $yystate) >= 0 &&
        $yyn <= $#yycheck && $yycheck[$yyn] == $yystate)
    {
        $yystate = $yytable[$yyn];
    } else {
        $yystate = $yydgoto[$yym];
    }
#if YYDEBUG
    print "yydebug: after reduction, shifting from state ",
        "$yyss[$yyssp] to state $yystate\n" if $yydebug;
#endif
    $yyss[++$yyssp] = $yystate;
    $yyvs[++$yyvsp] = $yyval;
  } # yyloop
} # yyparse
#line 118 "calc.y"

# Prompt the user on STDERR, but only prompt if STDERR and the input
# file are both terminals.

# read from STDIN if no files are named on the command line
unshift(@ARGV, '-') if $#ARGV < $[;

# After finishing a file, open the next one.  Return whether there
# really is a next one that was opened.
sub next_file
{
    while ($ARGV = shift(@ARGV)) {
	if (! open(ARGV, $ARGV)) {
	    print STDERR "$ARGV: cannot open file: $!\n";
	    next;
	}
	$prompt = (-t ARGV && -t STDERR) ? '(Calc) ' : '';
	last;
    }
    $ARGV >= $[;
}

# print he prompt
sub prompt
{
    print STDERR $prompt if $prompt;
}

# print an error message
sub yyerror
{
    print STDERR "\"$ARGV\", " if $ARGV ne '-';
    print STDERR "line $.: ", @_, "\n";
}

# Hand-coded lex until I write lex -p, too!
sub yylex
{
 lexloop:
    {
	# get a line of input, if we need it.
	if ($line eq '') {
	    &prompt;
	    $line = <ARGV>;
	    if ($line eq '') {
		close(ARGV);
		&next_file || return(0);
	    }
	}

	# Skip over white space, and grab the first character.
	# If there is no such character, then grab the next line.
	$line =~ s/^[ \t\f\r\v]*(.|\n)//	|| next lexloop;
	local($char) = $1;
	if ($char eq '#') {
	    # comment, so discard the line
	    $line = "\n";
	    &yylex;
	} elsif ($char =~ /^['"]/) {
	    # collect the string
	    if ($line =~ s/^([^$char]*)$char//) {
		$yylval = $1;
	    } else {
		&yyerror('unterminated string');
		$yylval = '';
	    }
	    $STRING;
	} elsif ($char =~ /^\d/) {
	    # number, is it integer or float?
	    if ($line =~ s/^(\d+)//) {
		$yylval = int($char . $1);
	    } else {
		$yylval = int($char);
	    }
	    $type = $INT;
	    if ($line =~ s/^(\.\d*)//) {
		$tmp = "0$1";
		$yylval += $tmp;
		$type = $FLOAT;
	    }
	    if ($line =~ s/^[eE]([-+]*\d+)//) {
		$yylval *= 10 ** $1;
		$type = $FLOAT;
	    }
	    $type;
	} elsif ($char =~ /^\w/) {
	    # identifier
	    $line =~ s/^([\w\d]*)//;
	    $yylval = $char.$1;
	    $IDENT;
	} elsif ($char eq '*' && $line =~ s/^\*//) {
	    $EXP;
	} elsif ($char eq '!' && $line =~ s/^=//) {
	    $NE;
	} elsif ($char eq '=' && $line =~ s/^=//) {
	    $EQ;
	} elsif ($char =~ /^[<>]/ && $line =~ s/^=//) {
	    $char eq '<' ? $LE : $GE;
	} elsif ($char =~ /^[<>]/ && $line =~ s/^$char//) {
	    $char eq '<' ? $L_SHIFT : $R_SHIFT;
	} else {
	    $yylval = $char;
	    ord($char);
	}
    }
}

# factorial
sub fact
{
    local($n) = @_;
    local($f) = 1;
    $f *= $n-- while ($n > 1) ;
    $f;
}

# catch signals
sub catch
{
    local($signum) = @_;
    print STDERR "\n" if (-t STDERR && -t STDIN);
    &yyerror("Floating point exception") if $signum = 8;
    next outer;
}
$SIG{'INT'} = 'catch';
$SIG{'FPE'} = 'catch';

select(STDERR); $| = 1;
select(STDOUT);
&next_file;

# main program
outer: while(1)
{
    $line = '';
    eval '$status = &yyparse;';
    exit $status if ! $@;
    &yyerror($@);
}
#line 657 "y.tab.py"
