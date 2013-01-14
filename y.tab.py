yysccsid = "@(#)yaccpar 1.8 (Berkeley) 01/20/91 (Python 2.0 12/31/92)";
#line 37 "smallcalc.y"
 
# Python Declarations *
import re
debug = 0
#line 8 "y.tab.py"
INT=257
FLOAT=258
STRING=259
IDENT=260
EQ=261
NE=262
PLUS=263
GT=264
GE=265
LT=266
LE=267
L_SHIFT=268
R_SHIFT=269
EXP=270
UNARY=271
YYERRCODE=256
yylhs = [                                               -1,
    0,    0,    1,    1,    1,    1,    1,    1,
]
yylen = [                                                2,
    1,    0,    3,    3,    3,    3,    3,    1,
]
yydefred = [                                             0,
    8,    0,    0,    0,    0,    0,    0,    0,    0,    3,
    0,    0,    6,    7,
]
yydgoto = [                                              3,
    4,
]
yysindex = [                                           -40,
    0,  -40,    0,  -39,  -28,  -40,  -40,  -40,  -40,    0,
  -26,  -26,    0,    0,
]
yyrindex = [                                             7,
    0,    0,    0,   18,    0,    0,    0,    0,    0,    0,
    1,    2,    0,    0,
]
yygindex = [                                             0,
    3,
]
YYTABLESIZE=217
yytable = [                                              2,
    4,    5,    8,    6,    5,    7,    2,    9,   11,   12,
   13,   14,   10,    8,    6,    8,    7,    1,    9,    0,
    9,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    4,    5,    4,    5,    4,    5,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    1,
]
yycheck = [                                             40,
    0,    0,   42,   43,    2,   45,    0,   47,    6,    7,
    8,    9,   41,   42,   43,   42,   45,    0,   47,   -1,
   47,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   41,   41,   43,   43,   45,   45,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,
]
YYFINAL=3
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
YYMAXTOKEN=271
#if YYDEBUG
yyname = [
"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"'!'",0,0,0,0,"'&'",0,"'('","')'","'*'","'+'",0,"'-'",0,"'/'",0,0,0,0,0,0,0,0,0,
0,0,0,0,"'='",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'|'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,"INT","FLOAT","STRING","IDENT","EQ","NE","PLUS","GT","GE","LT","LE",
"L_SHIFT","R_SHIFT","EXP","UNARY",
]
yyrule = [
"$accept : start_expr",
"start_expr : expr",
"start_expr :",
"expr : '(' expr ')'",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : INT",
]
#endif
import os, types
def yyclearin() :
    yychar = -1
def yyerrok() :
    yyerrflag = 0
yyss = [0]
yyvs = [0]
def YYERROR() :
  yynerrs=yynerrs+1
  yy_err_recover()

def yy_err_recover() :
  if yyerrflag < 3 :
    yyerrflag = 3
    while 1 :
      yyn = yysindex[yyss[yyssp]]
      if yyn :
        yyn = yyn + YYERRCODE
        if yyn >= 0 and yycheck[yyn] == YYERRCODE :
          yystate = yytable[yyn]
          yyssp=yyssp+1
          yyss.append( yystate )
          yyvsp=yyvsp+1
          yyvs.append( yylval )
          return 2 #next yyloop;
        else :
          if yyssp <= 0 :
            return 1
          yyssp=yyssp-1
          yyss.pop()
          yyvsp=yyvsp-1
          yyvs.pop()
  else :
    if yychar == 0 :
      return 1
    yychar = -1
    return 2 #next yyloop;
  return 0

def yyparse() :
  yydebug = int( os.environ.get('YYDEBUG','0') )
  yynerrs = 0
  yyerrflag = 0
  yychar = -1
  yyssp = 0
  yyvsp = 0
  yyss[yyssp] = 0
  yystate = 0
  #yyloop:
  while 1 :
    #yyreduce: 
    yyn = yydefred[yystate]
    if not yyn :
      if yychar < 0 :
        (yychar, yylval) = yylex()
        if type( yychar ) is types.StringType:
          yychar = ord( yychar )
        if yychar < 0 :
          yychar = 0
        if yydebug :
          print 'yydebug: state ', yystate, ', reading ', yychar, ' (', yyname[yychar], ')'
      yyn = yysindex[yystate]
      if yyn :
        yyn = yyn + yychar
        if yyn >= 0 and yycheck[yyn] == yychar :
          if yydebug :
            print 'yydebug: state ', yystate, ', shifting to state ', yytable[yyn]
          yystate = yytable[yyn]
          yyssp=yyssp+1
          yyss.append( yytable[yyn] )
          yyvsp=yyvsp+1
          yyvs.append( yylval )
          yychar = -1
          if yyerrflag > 0 :
            --yyerrflag 
          continue
      yyn = yyrindex[yystate]
      if yyn :
        yyn = yyn + yychar
        if yyn >= 0 and yycheck[yyn] == yychar :
          yyn = yytable[yyn]
      elif not yyerrflag :
        try :
          yyerror('syntax error')
        except:          print 'No yyerror function'
        yynerrs=yynerrs+1
      elif yy_err_recover() == 1 :
        return(1)
      elif yy_err_recover() == 2 :
        yychar = -1
        continue
    # yyreduce
    if yydebug :
      print 'yydebug: state ', yystate, ', reducing by rule ', yyn, ' (', yyrule[yyn], ')'
    yym = yylen[yyn]
    yyval = yyvs[yyvsp+1-yym]
    # switch:
    if yyn == 1 :
#line 46 "smallcalc.y"

      print "And the answer is ", yyvs[yyvsp-0]
    
    if yyn == 3 :
#line 53 "smallcalc.y"
 
      yyval = yyvs[yyvsp-1] 
    
    if yyn == 4 :
#line 57 "smallcalc.y"
 
      yyval = yyvs[yyvsp-2] + yyvs[yyvsp-0]
      if debug : print "sum=", yyval
    
    if yyn == 5 :
#line 62 "smallcalc.y"
 
      yyval = yyvs[yyvsp-2] - yyvs[yyvsp-0] 
    
    if yyn == 6 :
#line 66 "smallcalc.y"
 
      yyval = yyvs[yyvsp-2] * yyvs[yyvsp-0] 
      if debug : print "prod:", yyvs[yyvsp-2], "*", yyvs[yyvsp-0], "=", yyval
    
    if yyn == 7 :
#line 71 "smallcalc.y"
 
      yyval = yyvs[yyvsp-2] / yyvs[yyvsp-0] 
    
    if yyn == 8 :
#line 75 "smallcalc.y"
 
      yyval = yyvs[yyvsp-0]
    
#line 261 "y.tab.py"
    # switch
    yyssp = yyssp - yym
    yyss[-yym:] = []
    yystate = yyss[yyssp]
    yyvsp = yyvsp - yym
    yyvs[-yym:] = []
    yym = yylhs[yyn]
    if yystate == 0 and yym == 0 :
      if yydebug :
        print 'yydebug: after reduction, shifting from state 0 to (final) state ', YYFINAL
      yystate = YYFINAL
      yyssp=yyssp+1
      yyss.append( YYFINAL )
      yyvsp=yyvsp+1
      yyvs.append( yyval )
      if yychar < 0 :
        (yychar, yylval) = yylex()
        if type( yychar ) is types.StringType :
          yychar = ord( yychar )
        if yychar < 0 :
          yychar = 0
        if yydebug :
          print 'yydebug: state (final) ', YYFINAL, 'reading ', yychar
      if yychar == 0:
        return(0)
      continue
    yyn = yygindex[yym]
    if yyn :
      yyn = yyn + yystate
      if yyn >= 0 and yyn <= (len(yycheck)-1) and yycheck[yyn] == yystate :
        yystate = yytable[yyn]
      else :
        yystate = yydgoto[yym]
    else :
      yystate = yydgoto[yym]
    if yydebug :
      print 'yydebug: after reduction, shifting from state ', yyss[yyssp], ' to state ', yystate
    yyssp=yyssp+1
    yyss.append( yystate )
    yyvsp=yyvsp+1
    yyvs.append( yyval )
  # yyloop
# yyparse
#line 81 "smallcalc.y"

def yylex() :

  # 
  # You may return single punctuation characters as strings.
  #
  # The return value is a 2-tuple consisting of ( token, yylval ).
  #

  global line, debug

  # Whitspace
  m = re.match( "^(\s*)(.*)", line )

  if m :
    line = m.group( 2 )
  else :
    return ( 0, 0 )

  # Punctuation
  m = re.match( "^([\+\-\*\/])(.*)", line )
  if m : 
    line = m.group( 2 )
    if debug: print "sym = ", m.group(1)
    return ( m.group( 1 ), 0 )

  # Numbers
  m = re.match( "^(\d+)(.*)", line )
  if m : 
    line = m.group( 2 )
    if debug: print "num = ", m.group(1)
    return ( INT, int( m.group( 1 )) )

  # Anything else is unrecognized
  if len( line ) :
    try :
      yyerror()
    except NameError :
      print( "lex error '%s'" % line )

  # We're all out of input
  return ( 0, 0 )

while 1 :
  line = raw_input( "Enter expression (. to quit) " )

  if line == '.' :
    break
  else:
    yyparse()

#line 357 "y.tab.py"
