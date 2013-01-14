$yysccsid = "@(#)yaccpar 1.8 (Berkeley) 01/20/91 (Perl 2.0 12/31/92)";
#define YYBYACC 1
#line 3 "getdate.y"
;# 	Steven M. Bellovin (unc!smb)
;#	Dept. of Computer Science
;#	University of North Carolina at Chapel Hill
;#	@(#)getdate.y	2.13	9/16/86
;#
;#	Richard J. Ohnemus (rick@IMD.Sterling.COM)
;#	(Where do I work??? I'm not even sure who I am! 8-{)
;#	04/24/92  converted to PERL.
;#	07/06/92  New date format (MONTH NUMBER NUMBER ':' NUMBER ':' NUMBER)
;#		  suggested by Raphael Manfredi <ram@eiffel.com>.
;#	07/08/92  Fixed table search in &lookup.
;#		  Call &localtime with correct value in &monthadd.
;#	10/08/92  Numeric values starting with pattern '0+[89]' interpretted
;#		  correctly.
;#		  Corrected European Western and Eastern time offsets.
;#		  Borrowed code from timelocal.pl to determine timezone offset
;#		  from GMT.
;#	10/10/92  Handle time zone offsets correctly (sign was reversed).
;#		  Set global time zone variable ('ourzone') correctly.

package getdate;

$AM = 1;
$PM = 2;
$DAYLIGHT = 1;
$STANDARD = 2;
$MAYBE = 3;

@mdays = (31, 0, 31,  30, 31, 30,  31, 31, 30,  31, 30, 31);
$epoch = 1970;
$daysec = 24 * 60 * 60;
#line 36 "getdate.tab.pl"
$ID=257;
$MONTH=258;
$DAY=259;
$MERIDIAN=260;
$NUMBER=261;
$UNIT=262;
$MUNIT=263;
$SUNIT=264;
$ZONE=265;
$DAYZONE=266;
$AGO=267;
$YYERRCODE=256;
@yylhs = (                                               -1,
    0,    0,    1,    1,    1,    1,    1,    1,    7,    2,
    2,    2,    2,    2,    2,    2,    3,    3,    5,    5,
    5,    4,    4,    4,    4,    4,    4,    4,    4,    4,
    6,    6,    6,    6,    6,    6,    6,
);
@yylen = (                                                2,
    0,    2,    1,    1,    1,    1,    1,    1,    1,    2,
    3,    4,    4,    5,    6,    6,    1,    1,    1,    2,
    2,    3,    5,    2,    4,    5,    7,    3,    2,    3,
    2,    2,    2,    1,    1,    1,    2,
);
@yydefred = (                                             1,
    0,    0,    0,    0,   34,   35,   36,   17,   18,    2,
    3,    4,    5,    6,    0,    8,    0,   20,    0,   21,
   10,   31,   32,   33,    0,    0,   37,    0,    0,   30,
    0,    0,    0,   25,   12,   13,    0,    0,    0,    0,
   23,    0,   15,   16,   27,
);
@yydgoto = (                                              1,
   10,   11,   12,   13,   14,   15,   16,
);
@yysindex = (                                             0,
 -241, -255,  -37,  -47,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0, -259,    0,  -42,    0, -252,    0,
    0,    0,    0,    0, -249, -248,    0,  -44, -246,    0,
  -55,  -31, -235,    0,    0,    0, -234, -232,  -28, -256,
    0, -230,    0,    0,    0,
);
@yyrindex = (                                             0,
    0,    0,    1,   79,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   10,    0,   46,    0,   55,    0,
    0,    0,    0,    0,    0,    0,    0,   19,    0,    0,
   64,   28,    0,    0,    0,    0,    0,    0,   37,   73,
    0,    0,    0,    0,    0,
);
@yygindex = (                                             0,
    0,    0,    0,    0,    0,    0,    0,
);
$YYTABLESIZE=345;
@yytable = (                                             26,
   19,   29,   37,   43,   44,   17,   18,   27,   30,    7,
   25,   31,   32,   33,   34,   38,    2,    3,   28,    4,
    5,    6,    7,    8,    9,   39,   40,   22,   41,   42,
   45,    0,    0,    0,    0,    0,   26,    0,    0,    0,
    0,    0,    0,    0,    0,   24,    0,    0,    0,    0,
    0,    0,    0,    0,   29,    0,    0,    0,    0,    0,
    0,    0,    0,   11,    0,    0,    0,    0,    0,    0,
    0,    0,   14,    0,    0,    0,    0,    0,    9,    0,
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
    0,    0,    0,    0,   35,   36,    0,    0,    0,    0,
   19,   20,   21,    0,   22,   23,   24,    0,   28,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   19,   19,
    0,   19,   19,   19,   19,   19,   19,    7,    7,    0,
    7,    7,    7,    7,    7,    7,   28,   28,    0,   28,
   28,   28,   28,   28,   28,   22,   22,    0,   22,   22,
   22,   22,   22,   22,   26,   26,    0,   26,   26,   26,
   26,   26,   26,   24,   24,    0,    0,   24,   24,   24,
   24,   24,   29,   29,    0,    0,   29,   29,   29,   29,
   29,   11,   11,    0,    0,   11,   11,   11,   11,   11,
   14,   14,    0,    0,   14,   14,   14,   14,   14,    9,
    0,    0,    0,    9,    9,
);
@yycheck = (                                             47,
    0,   44,   58,  260,  261,  261,   44,  267,  261,    0,
   58,  261,  261,   58,  261,   47,  258,  259,    0,  261,
  262,  263,  264,  265,  266,  261,  261,    0,  261,   58,
  261,   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,    0,   -1,   -1,   -1,   -1,   -1,    0,   -1,
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
   -1,   -1,   -1,   -1,  260,  261,   -1,   -1,   -1,   -1,
  258,  259,  260,   -1,  262,  263,  264,   -1,  261,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  258,  259,
   -1,  261,  262,  263,  264,  265,  266,  258,  259,   -1,
  261,  262,  263,  264,  265,  266,  258,  259,   -1,  261,
  262,  263,  264,  265,  266,  258,  259,   -1,  261,  262,
  263,  264,  265,  266,  258,  259,   -1,  261,  262,  263,
  264,  265,  266,  258,  259,   -1,   -1,  262,  263,  264,
  265,  266,  258,  259,   -1,   -1,  262,  263,  264,  265,
  266,  258,  259,   -1,   -1,  262,  263,  264,  265,  266,
  258,  259,   -1,   -1,  262,  263,  264,  265,  266,  261,
   -1,   -1,   -1,  265,  266,
);
$YYFINAL=1;
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
$YYMAXTOKEN=267;
#if YYDEBUG
@yyname = (
"end-of-file",'','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','',
'','','','','','','','','','',"','",'','',"'/'",'','','','','','','','','','',"':'",'','','','','','','','','',
'','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','',
'','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','',
'','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','',
'','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','','',
'','','','','','','','','','','','','','','','','','','','','','','','','','','','','',"ID","MONTH","DAY",
"MERIDIAN","NUMBER","UNIT","MUNIT","SUNIT","ZONE","DAYZONE","AGO",
);
@yyrule = (
"\$accept : timedate",
"timedate :",
"timedate : timedate item",
"item : tspec",
"item : zone",
"item : dtspec",
"item : dyspec",
"item : rspec",
"item : nspec",
"nspec : NUMBER",
"tspec : NUMBER MERIDIAN",
"tspec : NUMBER ':' NUMBER",
"tspec : NUMBER ':' NUMBER MERIDIAN",
"tspec : NUMBER ':' NUMBER NUMBER",
"tspec : NUMBER ':' NUMBER ':' NUMBER",
"tspec : NUMBER ':' NUMBER ':' NUMBER MERIDIAN",
"tspec : NUMBER ':' NUMBER ':' NUMBER NUMBER",
"zone : ZONE",
"zone : DAYZONE",
"dyspec : DAY",
"dyspec : DAY ','",
"dyspec : NUMBER DAY",
"dtspec : NUMBER '/' NUMBER",
"dtspec : NUMBER '/' NUMBER '/' NUMBER",
"dtspec : MONTH NUMBER",
"dtspec : MONTH NUMBER ',' NUMBER",
"dtspec : MONTH NUMBER NUMBER ':' NUMBER",
"dtspec : MONTH NUMBER NUMBER ':' NUMBER ':' NUMBER",
"dtspec : MONTH NUMBER NUMBER",
"dtspec : NUMBER MONTH",
"dtspec : NUMBER MONTH NUMBER",
"rspec : NUMBER UNIT",
"rspec : NUMBER MUNIT",
"rspec : NUMBER SUNIT",
"rspec : UNIT",
"rspec : MUNIT",
"rspec : SUNIT",
"rspec : rspec AGO",
);
#endif
sub yyclearin { $yychar = -1; }
sub yyerrok { $yyerrflag = 0; }
$YYSTACKSIZE = $YYSTACKSIZE || $YYMAXDEPTH || 500;
$YYMAXDEPTH = $YYMAXDEPTH || $YYSTACKSIZE || 500;
$yyss[$YYSTACKSIZE] = 0;
$yyvs[$YYSTACKSIZE] = 0;
sub YYERROR { ++$yynerrs; &yy_err_recover; }
sub yy_err_recover
{
  if ($yyerrflag < 3)
  {
    $yyerrflag = 3;
    while (1)
    {
      if (($yyn = $yysindex[$yyss[$yyssp]]) && 
          ($yyn += $YYERRCODE) >= 0 && 
          $yycheck[$yyn] == $YYERRCODE)
      {
#if YYDEBUG
       print "yydebug: state $yyss[$yyssp], error recovery shifting",
             " to state $yytable[$yyn]\n" if $yydebug;
#endif
        $yyss[++$yyssp] = $yystate = $yytable[$yyn];
        $yyvs[++$yyvsp] = $yylval;
        next yyloop;
      }
      else
      {
#if YYDEBUG
        print "yydebug: error recovery discarding state ",
              $yyss[$yyssp], "\n"  if $yydebug;
#endif
        return(1) if $yyssp <= 0;
        --$yyssp;
        --$yyvsp;
      }
    }
  }
  else
  {
    return (1) if $yychar == 0;
#if YYDEBUG
    if ($yydebug)
    {
      $yys = '';
      if ($yychar <= $YYMAXTOKEN) { $yys = $yyname[$yychar]; }
      if (!$yys) { $yys = 'illegal-symbol'; }
      print "yydebug: state $yystate, error recovery discards ",
            "token $yychar ($yys)\n";
    }
#endif
    $yychar = -1;
    next yyloop;
  }
0;
} # yy_err_recover

sub yyparse
{
#ifdef YYDEBUG
  if ($yys = $ENV{'YYDEBUG'})
  {
    $yydebug = int($1) if $yys =~ /^(\d)/;
  }
#endif

  $yynerrs = 0;
  $yyerrflag = 0;
  $yychar = (-1);

  $yyssp = 0;
  $yyvsp = 0;
  $yyss[$yyssp] = $yystate = 0;

yyloop: while(1)
  {
    yyreduce: {
      last yyreduce if ($yyn = $yydefred[$yystate]);
      if ($yychar < 0)
      {
        if (($yychar = &yylex) < 0) { $yychar = 0; }
#if YYDEBUG
        if ($yydebug)
        {
          $yys = '';
          if ($yychar <= $#yyname) { $yys = $yyname[$yychar]; }
          if (!$yys) { $yys = 'illegal-symbol'; };
          print "yydebug: state $yystate, reading $yychar ($yys)\n";
        }
#endif
      }
      if (($yyn = $yysindex[$yystate]) && ($yyn += $yychar) >= 0 &&
              $yycheck[$yyn] == $yychar)
      {
#if YYDEBUG
        print "yydebug: state $yystate, shifting to state ",
              $yytable[$yyn], "\n"  if $yydebug;
#endif
        $yyss[++$yyssp] = $yystate = $yytable[$yyn];
        $yyvs[++$yyvsp] = $yylval;
        $yychar = (-1);
        --$yyerrflag if $yyerrflag > 0;
        next yyloop;
      }
      if (($yyn = $yyrindex[$yystate]) && ($yyn += $yychar) >= 0 &&
            $yycheck[$yyn] == $yychar)
      {
        $yyn = $yytable[$yyn];
        last yyreduce;
      }
      if (! $yyerrflag) {
        &yyerror('syntax error');
        ++$yynerrs;
      }
      return(1) if &yy_err_recover;
    } # yyreduce
#if YYDEBUG
    print "yydebug: state $yystate, reducing by rule ",
          "$yyn ($yyrule[$yyn])\n"  if $yydebug;
#endif
    $yym = $yylen[$yyn];
    $yyval = $yyvs[$yyvsp+1-$yym];
    switch:
    {
if ($yyn == 3) {
#line 41 "getdate.y"

		{
		    $timeflag++;
		
last switch;
} }
if ($yyn == 4) {
#line 45 "getdate.y"

		{
		    $zoneflag++;
		
last switch;
} }
if ($yyn == 5) {
#line 49 "getdate.y"

		{
		    $dateflag++;
		
last switch;
} }
if ($yyn == 6) {
#line 53 "getdate.y"

		{
		    $dayflag++;
		
last switch;
} }
if ($yyn == 7) {
#line 57 "getdate.y"

		{
		    $relflag++;
		
last switch;
} }
if ($yyn == 9) {
#line 64 "getdate.y"

		{
		    if ($timeflag && $dateflag && !$relflag) {
			$year = $yyvs[$yyvsp-0];
		    }
		    else {
			$timeflag++;
			$hh = int($yyvs[$yyvsp-0] / 100);
			$mm = $yyvs[$yyvsp-0] % 100;
			$ss = 0;
			$merid = 24;
		    }
		
last switch;
} }
if ($yyn == 10) {
#line 79 "getdate.y"

		{
		    $hh = $yyvs[$yyvsp-1];
		    $mm = 0;
		    $ss = 0;
		    $merid = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 11) {
#line 86 "getdate.y"

		{
		    $hh = $yyvs[$yyvsp-2];
		    $mm = $yyvs[$yyvsp-0];
		    $merid = 24;
		
last switch;
} }
if ($yyn == 12) {
#line 92 "getdate.y"

		{
		    $hh = $yyvs[$yyvsp-3];
		    $mm = $yyvs[$yyvsp-1];
		    $merid = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 13) {
#line 98 "getdate.y"

		{
		    $hh = $yyvs[$yyvsp-3];
		    $mm = $yyvs[$yyvsp-1];
		    $merid = 24;
		    $daylight = $STANDARD;
		    $ourzone = -($yyvs[$yyvsp-0] % 100 + 60 * int($yyvs[$yyvsp-0] / 100));
		
last switch;
} }
if ($yyn == 14) {
#line 106 "getdate.y"

		{
		    $hh = $yyvs[$yyvsp-4];
		    $mm = $yyvs[$yyvsp-2];
		    $ss = $yyvs[$yyvsp-0];
		    $merid = 24;
		
last switch;
} }
if ($yyn == 15) {
#line 113 "getdate.y"

		{
		    $hh = $yyvs[$yyvsp-5];
		    $mm = $yyvs[$yyvsp-3];
		    $ss = $yyvs[$yyvsp-1];
		    $merid = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 16) {
#line 120 "getdate.y"

		{
		    $hh = $yyvs[$yyvsp-5];
		    $mm = $yyvs[$yyvsp-3];
		    $ss = $yyvs[$yyvsp-1];
		    $merid = 24;
		    $daylight = $STANDARD;
		    $ourzone = -($yyvs[$yyvsp-0] % 100 + 60 * int($yyvs[$yyvsp-0] / 100));
		
last switch;
} }
if ($yyn == 17) {
#line 131 "getdate.y"

		{
		    $ourzone = $yyvs[$yyvsp-0];
		    $daylight = $STANDARD;
		
last switch;
} }
if ($yyn == 18) {
#line 136 "getdate.y"

		{
		    $ourzone = $yyvs[$yyvsp-0];
		    $daylight = $DAYLIGHT;
		
last switch;
} }
if ($yyn == 19) {
#line 143 "getdate.y"

		{
		    $dayord = 1;
		    $dayreq = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 20) {
#line 148 "getdate.y"

		{
		    $dayord = 1;
		    $dayreq = $yyvs[$yyvsp-1];
		
last switch;
} }
if ($yyn == 21) {
#line 153 "getdate.y"

		{
		    $dayord = $yyvs[$yyvsp-1];
		    $dayreq = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 22) {
#line 160 "getdate.y"

		{
		    $month = $yyvs[$yyvsp-2];
		    $day = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 23) {
#line 165 "getdate.y"

		{
		    #
;# 		     * HACK ALERT!!!!
;# 		     * The 1000 is a magic number to attempt to force
;# 		     * use of 4 digit years if year/month/day can be
;# 		     * parsed. This was only done for backwards
;# 		     * compatibility in rh.
;# 		     

		    if ($yyvs[$yyvsp-4] > 1000) {
			$year = $yyvs[$yyvsp-4];
			$month = $yyvs[$yyvsp-2];
			$day = $yyvs[$yyvsp-0];
		    }
		    else {
			$month = $yyvs[$yyvsp-4];
			$day = $yyvs[$yyvsp-2];
			$year = $yyvs[$yyvsp-0];
		    }
		
last switch;
} }
if ($yyn == 24) {
#line 185 "getdate.y"

		{
		    $month = $yyvs[$yyvsp-1];
		    $day = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 25) {
#line 190 "getdate.y"

		{
		    $month = $yyvs[$yyvsp-3];
		    $day = $yyvs[$yyvsp-2];
		    $year = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 26) {
#line 196 "getdate.y"

		{
		    $month = $yyvs[$yyvsp-4];
		    $day = $yyvs[$yyvsp-3];
		    $hh = $yyvs[$yyvsp-2];
		    $mm = $yyvs[$yyvsp-0];
		    $merid = 24;
		    $timeflag++;
		
last switch;
} }
if ($yyn == 27) {
#line 205 "getdate.y"

		{
		    $month = $yyvs[$yyvsp-6];
		    $day = $yyvs[$yyvsp-5];
		    $hh = $yyvs[$yyvsp-4];
		    $mm = $yyvs[$yyvsp-2];
		    $ss = $yyvs[$yyvsp-0];
		    $merid = 24;
		    $timeflag++;
		
last switch;
} }
if ($yyn == 28) {
#line 215 "getdate.y"

		{
		    $month = $yyvs[$yyvsp-2];
		    $day = $yyvs[$yyvsp-1];
		    $year = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 29) {
#line 221 "getdate.y"

		{
		    $month = $yyvs[$yyvsp-0];
		    $day = $yyvs[$yyvsp-1];
		
last switch;
} }
if ($yyn == 30) {
#line 226 "getdate.y"

		{
		    $month = $yyvs[$yyvsp-1];
		    $day = $yyvs[$yyvsp-2];
		    $year = $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 31) {
#line 234 "getdate.y"

		{
		    $relsec += 60 * $yyvs[$yyvsp-1] * $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 32) {
#line 238 "getdate.y"

		{
		    $relmonth += $yyvs[$yyvsp-1] * $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 33) {
#line 242 "getdate.y"

		{
		    $relsec += $yyvs[$yyvsp-1];
		
last switch;
} }
if ($yyn == 34) {
#line 246 "getdate.y"

		{
		    $relsec +=  60 * $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 35) {
#line 250 "getdate.y"

		{
		    $relmonth += $yyvs[$yyvsp-0];
		
last switch;
} }
if ($yyn == 36) {
#line 254 "getdate.y"

		{
		    $relsec++;
		
last switch;
} }
if ($yyn == 37) {
#line 258 "getdate.y"

		{
		    $relsec = -$relsec;
		    $relmonth = -$relmonth;
		
last switch;
} }
#line 690 "getdate.tab.pl"
    } # switch
    $yyssp -= $yym;
    $yystate = $yyss[$yyssp];
    $yyvsp -= $yym;
    $yym = $yylhs[$yyn];
    if ($yystate == 0 && $yym == 0)
    {
#if YYDEBUG
      print "yydebug: after reduction, shifting from state 0 ",
            "to state $YYFINAL\n" if $yydebug;
#endif
      $yystate = $YYFINAL;
      $yyss[++$yyssp] = $YYFINAL;
      $yyvs[++$yyvsp] = $yyval;
      if ($yychar < 0)
      {
        if (($yychar = &yylex) < 0) { $yychar = 0; }
#if YYDEBUG
        if ($yydebug)
        {
          $yys = '';
          if ($yychar <= $#yyname) { $yys = $yyname[$yychar]; }
          if (!$yys) { $yys = 'illegal-symbol'; }
          print "yydebug: state $YYFINAL, reading $yychar ($yys)\n";
        }
#endif
      }
      return(0) if $yychar == 0;
      next yyloop;
    }
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
#line 265 "getdate.y"

sub dateconv
{
    local($mm, $dd, $yy, $h, $m, $s, $mer, $zone, $dayflag) = @_;
    local($time_of_day, $jdate);
    local($i);

    if ($yy < 0) {
	$yy = -$yy;
    }
    if ($yy < 100) {
	$yy += 1900;
    }
    $mdays[1] =
	28 + (($yy % 4) == 0 && (($yy % 100) != 0 || ($yy % 400) == 0));
    if ($yy < $epoch || $yy > 2001 || $mm < 1 || $mm > 12
	|| $dd < 1 || $dd > $mdays[--$mm]) {
	return -1;
    }
    $jdate = $dd - 1;
    for ($i = 0; $i < $mm; $i++) {
	$jdate += $mdays[$i];
    }
    for ($i = $epoch; $i < $yy; $i++) {
	$jdate += 365 + (($i % 4) == 0);
    }
    $jdate *= $daysec;
    $jdate += $zone * 60;
    if (($time_of_day = &timeconv($h, $m, $s, $mer)) < 0) {
	return -1;
    }
    $jdate += $time_of_day;
    if ($dayflag == $DAYLIGHT
	|| ($dayflag == $MAYBE && (localtime($jdate))[8])) {
	$jdate -= 60 * 60;
    }
    return $jdate;
}

sub dayconv
{
    local($ordday, $day, $now) = @_;
    local(@loctime);
    local($time_of_day);

    $time_of_day = $now;
    @loctime = localtime($time_of_day);
    $time_of_day += $daysec * (($day - $loctime[6] + 7) % 7);
    $time_of_day += 7 * $daysec * ($ordday <= 0 ? $ordday : $ordday - 1);
    return &daylcorr($time_of_day, $now);
}

sub timeconv
{
    local($hh, $mm, $ss, $mer) = @_;

    return -1 if ($mm < 0 || $mm > 59 || $ss < 0 || $ss > 59);

    if ($mer == $AM) {
	return -1 if ($hh < 1 || $hh > 12);
	return 60 * (($hh % 12) * 60 + $mm) + $ss;
    }
    if ($mer == $PM) {
	return -1 if ($hh < 1 || $hh > 12);
	return 60 * (($hh % 12 + 12) * 60 + $mm) + $ss;
    }
    if ($mer == 24) {
	return -1 if ($hh < 0 || $hh > 23);
	return 60 * ($hh * 60 + $mm) + $ss;
    }
    return -1;
}

sub monthadd
{
    local($sdate, $relmonth) = @_;
    local(@ltime);
    local($mm, $yy);
    
    return 0 if ($relmonth == 0);

    @ltime = localtime($sdate);
    $mm = 12 * $ltime[5] + $ltime[4] + $relmonth;
    $yy = int($mm / 12);
    $mm = $mm % 12 + 1;
    return &daylcorr(&dateconv($mm, $ltime[3], $yy, $ltime[2],
			       $ltime[1], $ltime[0], 24, $ourzone, $MAYBE),
		     $sdate);
}

sub daylcorr
{
    local($future, $now) = @_;
    local($fdayl, $nowdayl);

    $nowdayl = ((localtime($now))[2] + 1) % 24;
    $fdayl = ((localtime($future))[2] + 1) % 24;
    return ($future - $now) + 60 * 60 * ($nowdayl - $fdayl);
}

sub yylex
{
    local($pcnt, $sign);

    while (1) {
	$dtstr =~ s/^\s*//;
	
	if ($dtstr =~ /^([-+])/) {
	    $sign = ($1 eq '-') ? -1 : 1;
	    $dtstr =~ s/^.//;
	    if ($dtstr =~ /^(\d+)/) {
		$num = $1;
		$num =~ s/^0+//;
		if ($num eq '') {
		    $yylval = 0;
		}
		else {
		    $yylval = eval "$num * $sign";
		}
		$dtstr =~ s/^\d+//;
		return $NUMBER;
	    }
	    else {
		return &yylex;
	    }
	}
	elsif ($dtstr =~ /^(\d+)/) {
	    $num = $1;
	    $num =~ s/^0+//;
	    if ($num eq '') {
		$yylval = 0;
	    }
	    else {
		$yylval = eval "$num";
	    }
	    $dtstr =~ s/^\d+//;
	    return $NUMBER;
	}
	elsif ($dtstr =~ /^([a-zA-z][a-zA-Z.]*)/) {
	    $dtstr = substr($dtstr, length($1));
	    return &lookup($1);
	}
	elsif ($dtstr =~ /^\(/) {
	    $pcnt = 0;
	    do {
		$dtstr = s/^(.)//;
		return 0 if !defined($1);
		$pcnt++ if ($1 eq '(');
		$pcnt-- if ($1 eq ')');
	    } while ($pcnt > 0);
	}
	else {
	    $yylval = ord(substr($dtstr, 0, 1));
	    $dtstr =~ s/^.//;
	    return $yylval;
	}
    }
}


%mdtab = (
	  "January",	"$MONTH,1",
	  "February",	"$MONTH,2",
	  "March", 	"$MONTH,3",
	  "April",	"$MONTH,4",
	  "May",	"$MONTH,5",
	  "June",	"$MONTH,6",
	  "July",	"$MONTH,7",
	  "August",	"$MONTH,8",
	  "September",	"$MONTH,9",
	  "Sept",	"$MONTH,9",
	  "October",	"$MONTH,10",
	  "November",	"$MONTH,11",
	  "December",	"$MONTH,12",

	  "Sunday",	"$DAY,0",
	  "Monday",	"$DAY,1",
	  "Tuesday",	"$DAY,2",
	  "Tues",	"$DAY,2",
	  "Wednesday",	"$DAY,3",
	  "Wednes",	"$DAY,3",
	  "Thursday",	"$DAY,4",
	  "Thur",	"$DAY,4",
	  "Thurs",	"$DAY,4",
	  "Friday",	"$DAY,5",
	  "Saturday",	"$DAY,6"
	  );

$HRS='*60';
$HALFHR='30';

%mztab = (
	  "a.m.",	"$MERIDIAN,$AM",
	  "am",		"$MERIDIAN,$AM",
	  "p.m.",	"$MERIDIAN,$PM",
	  "pm",		"$MERIDIAN,$PM",
	  "nst",	"$ZONE,3 $HRS + $HALFHR",	# Newfoundland
	  "n.s.t.",	"$ZONE,3 $HRS + $HALFHR",
	  "ast",	"$ZONE,4 $HRS",			# Atlantic
	  "a.s.t.",	"$ZONE,4 $HRS",
	  "adt",	"$DAYZONE,4 $HRS",
	  "a.d.t.",	"$DAYZONE,4 $HRS",
	  "est",	"$ZONE,5 $HRS",			# Eastern
	  "e.s.t.",	"$ZONE,5 $HRS",
	  "edt",	"$DAYZONE,5 $HRS",
	  "e.d.t.",	"$DAYZONE,5 $HRS",
	  "cst",	"$ZONE,6 $HRS",			# Central
	  "c.s.t.",	"$ZONE,6 $HRS",
	  "cdt",	"$DAYZONE,6 $HRS",
	  "c.d.t.",	"$DAYZONE,6 $HRS",
	  "mst",	"$ZONE,7 $HRS",			# Mountain
	  "m.s.t.",	"$ZONE,7 $HRS",
	  "mdt",	"$DAYZONE,7 $HRS",
	  "m.d.t.",	"$DAYZONE,7 $HRS",
	  "pst",	"$ZONE,8 $HRS",			# Pacific
	  "p.s.t.",	"$ZONE,8 $HRS",
	  "pdt",	"$DAYZONE,8 $HRS",
	  "p.d.t.",	"$DAYZONE,8 $HRS",
	  "yst",	"$ZONE,9 $HRS",			# Yukon
	  "y.s.t.",	"$ZONE,9 $HRS",
	  "ydt",	"$DAYZONE,9 $HRS",
	  "y.d.t.",	"$DAYZONE,9 $HRS",
	  "hst",	"$ZONE,10 $HRS",		# Hawaii
	  "h.s.t.",	"$ZONE,10 $HRS",
	  "hdt",	"$DAYZONE,10 $HRS",
	  "h.d.t.",	"$DAYZONE,10 $HRS",

	  "gmt",	"$ZONE,0 $HRS",
	  "g.m.t.",	"$ZONE,0 $HRS",
	  "bst",	"$DAYZONE,0 $HRS",		# British Summer Time
	  "b.s.t.",	"$DAYZONE,0 $HRS",
	  "wet",	"$ZONE,0 $HRS ",		# Western European Time
	  "w.e.t.",	"$ZONE,0 $HRS ",
	  "west",	"$DAYZONE,0 $HRS",		# Western European Summer Time
	  "w.e.s.t.",	"$DAYZONE,0 $HRS",

	  "met",	"$ZONE,-1 $HRS",		# Middle European Time
	  "m.e.t.",	"$ZONE,-1 $HRS",
	  "mest",	"$DAYZONE,-1 $HRS",		# Middle European Summer Time
	  "m.e.s.t.",	"$DAYZONE,-1 $HRS",
	  "eet",	"$ZONE,-2 $HRS",		# European Eastern Time
	  "e.e.t.",	"$ZONE,-2 $HRS",
	  "eest",	"$DAYZONE,-2 $HRS",		# European Eastern Summer Time
	  "e.e.s.t.",	"$DAYZONE,-2 $HRS",
	  "jst",	"$ZONE,-9 $HRS",		# Japan Standard Time
	  "j.s.t.",	"$ZONE,-9 $HRS",		# Japan Standard Time
	  						# No daylight savings time

	  "aest",	"$ZONE,-10 $HRS",		# Australian Eastern Time
	  "a.e.s.t.",	"$ZONE,-10 $HRS",
	  "aesst",	"$DAYZONE,-10 $HRS",		# Australian Eastern Summer Time
	  "a.e.s.s.t.",	"$DAYZONE,-10 $HRS",
	  "acst",	"$ZONE,-(9 $HRS + $HALFHR)",	# Australian Central Time
	  "a.c.s.t.",	"$ZONE,-(9 $HRS + $HALFHR)",
	  "acsst",	"$DAYZONE,-(9 $HRS + $HALFHR)",	# Australian Central Summer
	  "a.c.s.s.t.",	"$DAYZONE,-(9 $HRS + $HALFHR)",
	  "awst",	"$ZONE,-8 $HRS",		# Australian Western Time
	  "a.w.s.t.",	"$ZONE,-8 $HRS"			# (no daylight time there, I'm told)
	  );

%unittab = (
	   "year",	"$MUNIT,12",
	   "month",	"$MUNIT,1",
	   "fortnight",	"$UNIT,14*24*60",
	   "week",	"$UNIT,7*24*60",
	   "day",	"$UNIT,1*24*60",
	   "hour",	"$UNIT,60",
	   "minute",	"$UNIT,1",
	   "min",	"$UNIT,1",
	   "second",	"$SUNIT,1",
	   "sec",	"$SUNIT,1"
	   );

%othertab = (
	    "tomorrow",	"$UNIT,1*24*60",
	    "yesterday","$UNIT,-1*24*60",
	    "today",	"$UNIT,0",
	    "now",	"$UNIT,0",
	    "last",	"$NUMBER,-1",
	    "this",	"$UNIT,0",
	    "next",	"$NUMBER,2",
	    "first",	"$NUMBER,1",
	    # "second",	"$NUMBER,2",
	    "third",	"$NUMBER,3",
	    "fourth",	"$NUMBER,4",
	    "fifth",	"$NUMBER,5",
	    "sixth",	"$NUMBER,6",
	    "seventh",	"$NUMBER,7",
	    "eigth",	"$NUMBER,8",
	    "ninth",	"$NUMBER,9",
	    "tenth",	"$NUMBER,10",
	    "eleventh",	"$NUMBER,11",
	    "twelfth",	"$NUMBER,12",
	    "ago",	"$AGO,1"
	    );

%milzone = (
	    "a",	"$ZONE,1 $HRS",
	    "b",	"$ZONE,2 $HRS",
	    "c",	"$ZONE,3 $HRS",
	    "d",	"$ZONE,4 $HRS",
	    "e",	"$ZONE,5 $HRS",
	    "f",	"$ZONE,6 $HRS",
	    "g",	"$ZONE,7 $HRS",
	    "h",	"$ZONE,8 $HRS",
	    "i",	"$ZONE,9 $HRS",
	    "k",	"$ZONE,10 $HRS",
	    "l",	"$ZONE,11 $HRS",
	    "m",	"$ZONE,12 $HRS",
	    "n",	"$ZONE,-1 $HRS",
	    "o",	"$ZONE,-2 $HRS",
	    "p",	"$ZONE,-3 $HRS",
	    "q",	"$ZONE,-4 $HRS",
	    "r",	"$ZONE,-5 $HRS",
	    "s",	"$ZONE,-6 $HRS",
	    "t",	"$ZONE,-7 $HRS",
	    "u",	"$ZONE,-8 $HRS",
	    "v",	"$ZONE,-9 $HRS",
	    "w",	"$ZONE,-10 $HRS",
	    "x",	"$ZONE,-11 $HRS",
	    "y",	"$ZONE,-12 $HRS",
	    "z",	"$ZONE,0 $HRS"
	    );

sub lookup
{
    local($id) = @_;
    local($abbrev, $idvar, $key, $token);

    $idvar = $id;
    if (length($idvar) == 3) {
	$abbrev = 1;
    }
    elsif (length($idvar) == 4 && substr($idvar, 3, 1) eq '.') {
	$abbrev = 1;
	$idvar = substr($idvar, 0, 3);
    }
    else {
	$abbrev = 0;
    }

    substr($idvar, 0, 1) =~ tr/a-z/A-Z/;
    if (defined($mdtab{$idvar})) {
	($token, $yylval) = split(/,/,$mdtab{$idvar});
	$yylval = eval "$yylval";
	return $token;
    }
    foreach $key (keys %mdtab) {
	if ($idvar eq substr($key, 0, 3)) {
	    ($token, $yylval) = split(/,/,$mdtab{$key});
	    $yylval = eval "$yylval";
	    return $token;
	}
    }
    
    $idvar = $id;
    if (defined($mztab{$idvar})) {
	($token, $yylval) = split(/,/,$mztab{$idvar});
	$yylval = eval "$yylval";
	return $token;
    }
    
    $idvar =~ tr/A-Z/a-z/;
    if (defined($mztab{$idvar})) {
	($token, $yylval) = split(/,/,$mztab{$idvar});
	$yylval = eval "$yylval";
	return $token;
    }
    
    $idvar = $id;
    if (defined($unittab{$idvar})) {
	($token, $yylval) = split(/,/,$unittab{$idvar});
	$yylval = eval "$yylval";
	return $token;
    }
    
    if ($idvar =~ /s$/) {
	$idvar =~ s/s$//;
    }
    if (defined($unittab{$idvar})) {
	($token, $yylval) = split(/,/,$unittab{$idvar});
	$yylval = eval "$yylval";
	return $token;
    }
    
    $idvar = $id;
    if (defined($othertab{$idvar})) {
	($token, $yylval) = split(/,/,$othertab{$idvar});
	$yylval = eval "$yylval";
	return $token;
    }
    
    if (length($idvar) == 1 && $idvar =~ /[a-zA-Z]/) {
	$idvar =~ tr/A-Z/a-z/;
	if (defined($milzone{$idvar})) {
	    ($token, $yylval) = split(/,/,$milzone{$idvar});
	    $yylval = eval "$yylval";
	    return $token;
	}
    }
    
    return $ID;
}

sub main'getdate
{
    local($now);
    local(@lt);
    local($sdate);
    local($TZ);

    ($dtstr, $now, $ourzone) = @_;

    if (!$now) {
	$now = time;
    }

    if (!$ourzone) {
	$TZ = defined($ENV{'TZ'}) ? ($ENV{'TZ'} ? $ENV{'TZ'} : '') : '';
	if($TZ =~
	   /^([^:\d+\-,]{3,})([+-]?\d{1,2}(:\d{1,2}){0,2})([^\d+\-,]{3,})?/) {
	    $ourzone = $2 * 60;
	}
	else {
	    @lt = localtime(0);
	    $ourzone = $lt[2] * 60 + $lt[1];		# minutes east of GMT
	    if ($ourzone > 0) {
		$ourzone = 24 * 60 - $ourzone;		# minutes west of GMT
	        $ourzone -= 24 * 60 if $lt[5] == 70;	# account for date line
	    }
	}
    }

    @lt = localtime($now);
    $year = 0;
    $month = $lt[4] + 1;
    $day = $lt[3];
    $relsec = $relmonth = 0;
    $timeflag = $zoneflag = $dateflag = $dayflag = $relflag = 0;
    $daylight = $MAYBE;
    $hh = $mm = $ss = 0;
    $merid = 24;
    
    $dtstr =~ tr/A-Z/a-z/;

    return -1 if &yyparse;
    
    return -1 if ($timeflag > 1 || $zoneflag > 1 || $dateflag > 1 || $dayflag > 1);

    if (!$year) {
	$year = ($month > ($lt[4] + 1)) ? ($lt[5] - 1) : $lt[5];
    }

    if ($dateflag || $timeflag || $dayflag) {
	$sdate = &dateconv($month, $day, $year, $hh, $mm, $ss,
			   $merid, $ourzone, $daylight);
	if ($sdate < 0) {
	    return -1;
	}
    }
    else {
	$sdate = $now;
	if ($relflag == 0) {
	    $sdate -= ($lt[0] + $lt[1] * 60 + $lt[2] * (60 * 60));
	}
    }
    
    $sdate += $relsec + &monthadd($sdate, $relmonth);
    $sdate += &dayconv($dayord, $dayreq, $sdate) if ($dayflag && !$dateflag);
    
    return $sdate;
}

sub yyerror
{
}

1;
#line 1215 "getdate.tab.pl"
