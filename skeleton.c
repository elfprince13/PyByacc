#include "defs.h"

/*  The banner used here should be replaced with an #ident directive    */
/*  if the target C compiler supports #ident directives.                */
/*                                                                      */
/*  If the skeleton is changed, the banner should be changed so that    */
/*  the altered version can easily be distinguished from the original.  */

static char *c_banner[] =
{
    "#ifndef lint",
    "static char yysccsid[] = \"@(#)yaccpar 1.8 (Berkeley) 01/20/91\";",
    "#endif",
    "#define YYBYACC 1",
    (char *) NULL
};

static char *perl_banner[] =
{
    "$yysccsid = \"@(#)yaccpar 1.8 (Berkeley) 01/20/91 (Perl 2.0 12/31/92)\";",
    "#define YYBYACC 1",
    (char *) NULL
};
  
static char *python_banner[] =
{
    "yysccsid = \"@(#)yaccpar 1.8 (Berkeley) 01/20/91 (Python 2.0 12/31/92)\";",
    (char *) NULL
};
  
char **banner[] = { c_banner, perl_banner, python_banner };

static char *c_tables[] =
{
    "extern short yylhs[];",
    "extern short yylen[];",
    "extern short yydefred[];",
    "extern short yydgoto[];",
    "extern short yysindex[];",
    "extern short yyrindex[];",
    "extern short yygindex[];",
    "extern short yytable[];",
    "extern short yycheck[];",
    "#if YYDEBUG",
    "extern char *yyname[];",
    "extern char *yyrule[];",
    "#endif",
    (char *) NULL
};

char **tables[] = { c_tables, (char **) NULL, (char **)NULL };

static char *c_header[] =
{
    "#define yyclearin (yychar=(-1))",
    "#define yyerrok (yyerrflag=0)",
    "#ifdef YYSTACKSIZE",
    "#ifndef YYMAXDEPTH",
    "#define YYMAXDEPTH YYSTACKSIZE",
    "#endif",
    "#else",
    "#ifdef YYMAXDEPTH",
    "#define YYSTACKSIZE YYMAXDEPTH",
    "#else",
    "#define YYSTACKSIZE 500",
    "#define YYMAXDEPTH 500",
    "#endif",
    "#endif",
    "int yydebug;",
    "int yynerrs;",
    "int yyerrflag;",
    "int yychar;",
    "short *yyssp;",
    "YYSTYPE *yyvsp;",
    "YYSTYPE yyval;",
    "YYSTYPE yylval;",
    "short yyss[YYSTACKSIZE];",
    "YYSTYPE yyvs[YYSTACKSIZE];",
    "#define yystacksize YYSTACKSIZE",
    (char *) NULL
};

static char *perl_header[] =
{
    "sub yyclearin { $yychar = -1; }",
    "sub yyerrok { $yyerrflag = 0; }",
    "$YYSTACKSIZE = $YYSTACKSIZE || $YYMAXDEPTH || 500;",
    "$YYMAXDEPTH = $YYMAXDEPTH || $YYSTACKSIZE || 500;",
    "$yyss[$YYSTACKSIZE] = 0;",
    "$yyvs[$YYSTACKSIZE] = 0;",
    (char *) NULL
};

static char *python_header[] =
{
    "import os, types",
    "def yyclearin() :",
    "    yychar = -1",
    "def yyerrok() :",
    "    yyerrflag = 0",
    "yyss = [0]",
    "yyvs = [0]",
    (char *) NULL
};

char **header[] = { c_header, perl_header, python_header };

static char *c_body[] =
{
    "#define YYABORT goto yyabort",
    "#define YYACCEPT goto yyaccept",
    "#define YYERROR goto yyerrlab",
    "int",
    "yyparse()",
    "{",
    "    register int yym, yyn, yystate;",
    "#if YYDEBUG",
    "    register char *yys;",
    "    extern char *getenv();",
    "",
    "    if (yys = getenv(\"YYDEBUG\"))",
    "    {",
    "        yyn = *yys;",
    "        if (yyn >= '0' && yyn <= '9')",
    "            yydebug = yyn - '0';",
    "    }",
    "#endif",
    "",
    "    yynerrs = 0;",
    "    yyerrflag = 0;",
    "    yychar = (-1);",
    "",
    "    yyssp = yyss;",
    "    yyvsp = yyvs;",
    "    *yyssp = yystate = 0;",
    "",
    "yyloop:",
    "    if (yyn = yydefred[yystate]) goto yyreduce;",
    "    if (yychar < 0)",
    "    {",
    "        if ((yychar = yylex()) < 0) yychar = 0;",
    "#if YYDEBUG",
    "        if (yydebug)",
    "        {",
    "            yys = 0;",
    "            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];",
    "            if (!yys) yys = \"illegal-symbol\";",
    "            printf(\"yydebug: state %d, reading %d (%s)\\n\", yystate,",
    "                    yychar, yys);",
    "        }",
    "#endif",
    "    }",
    "    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&",
    "            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)",
    "    {",
    "#if YYDEBUG",
    "        if (yydebug)",
    "            printf(\"yydebug: state %d, shifting to state %d\\n\",",
    "                    yystate, yytable[yyn]);",
    "#endif",
    "        if (yyssp >= yyss + yystacksize - 1)",
    "        {",
    "            goto yyoverflow;",
    "        }",
    "        *++yyssp = yystate = yytable[yyn];",
    "        *++yyvsp = yylval;",
    "        yychar = (-1);",
    "        if (yyerrflag > 0)  --yyerrflag;",
    "        goto yyloop;",
    "    }",
    "    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&",
    "            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)",
    "    {",
    "        yyn = yytable[yyn];",
    "        goto yyreduce;",
    "    }",
    "    if (yyerrflag) goto yyinrecovery;",
    "#ifdef lint",
    "    goto yynewerror;",
    "#endif",
    "yynewerror:",
    "    yyerror(\"syntax error\");",
    "#ifdef lint",
    "    goto yyerrlab;",
    "#endif",
    "yyerrlab:",
    "    ++yynerrs;",
    "yyinrecovery:",
    "    if (yyerrflag < 3)",
    "    {",
    "        yyerrflag = 3;",
    "        for (;;)",
    "        {",
    "            if ((yyn = yysindex[*yyssp]) && (yyn += YYERRCODE) >= 0 &&",
    "                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)",
    "            {",
    "#if YYDEBUG",
    "                if (yydebug)",
    "                    printf(\"yydebug: state %d, error recovery shifting\\",
    " to state %d\\n\", *yyssp, yytable[yyn]);",
    "#endif",
    "                if (yyssp >= yyss + yystacksize - 1)",
    "                {",
    "                    goto yyoverflow;",
    "                }",
    "                *++yyssp = yystate = yytable[yyn];",
    "                *++yyvsp = yylval;",
    "                goto yyloop;",
    "            }",
    "            else",
    "            {",
    "#if YYDEBUG",
    "                if (yydebug)",
    "                    printf(\"yydebug: error recovery discarding state %d\
\\n\",",
    "                            *yyssp);",
    "#endif",
    "                if (yyssp <= yyss) goto yyabort;",
    "                --yyssp;",
    "                --yyvsp;",
    "            }",
    "        }",
    "    }",
    "    else",
    "    {",
    "        if (yychar == 0) goto yyabort;",
    "#if YYDEBUG",
    "        if (yydebug)",
    "        {",
    "            yys = 0;",
    "            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];",
    "            if (!yys) yys = \"illegal-symbol\";",
    "            printf(\"yydebug: state %d, error recovery discards token %d\
 (%s)\\n\",",
    "                    yystate, yychar, yys);",
    "        }",
    "#endif",
    "        yychar = (-1);",
    "        goto yyloop;",
    "    }",
    "yyreduce:",
    "#if YYDEBUG",
    "    if (yydebug)",
    "        printf(\"yydebug: state %d, reducing by rule %d (%s)\\n\",",
    "                yystate, yyn, yyrule[yyn]);",
    "#endif",
    "    yym = yylen[yyn];",
    "    yyval = yyvsp[1-yym];",
    "    switch (yyn)",
    "    {",
    (char *) NULL
};

static char *perl_body[] =
{
    "sub YYERROR { ++$yynerrs; &yy_err_recover; }",
    "sub yy_err_recover",
    "{",
    "  if ($yyerrflag < 3)",
    "  {",
    "    $yyerrflag = 3;",
    "    while (1)",
    "    {",
    "      if (($yyn = $yysindex[$yyss[$yyssp]]) && ",
    "          ($yyn += $YYERRCODE) >= 0 && ",
    "          $yycheck[$yyn] == $YYERRCODE)",
    "      {",
    "#if YYDEBUG",
    "       print \"yydebug: state $yyss[$yyssp], error recovery shifting\",",
    "             \" to state $yytable[$yyn]\\n\" if $yydebug;",
    "#endif",
    "        $yyss[++$yyssp] = $yystate = $yytable[$yyn];",
    "        $yyvs[++$yyvsp] = $yylval;",
    "        next yyloop;",
    "      }",
    "      else",
    "      {",
    "#if YYDEBUG",
    "        print \"yydebug: error recovery discarding state \",",
    "              $yyss[$yyssp], \"\\n\"  if $yydebug;",
    "#endif",
    "        return(1) if $yyssp <= 0;",
    "        --$yyssp;",
    "        --$yyvsp;",
    "      }",
    "    }",
    "  }",
    "  else",
    "  {",
    "    return (1) if $yychar == 0;",
    "#if YYDEBUG",
    "    if ($yydebug)",
    "    {",
    "      $yys = '';",
    "      if ($yychar <= $YYMAXTOKEN) { $yys = $yyname[$yychar]; }",
    "      if (!$yys) { $yys = 'illegal-symbol'; }",
    "      print \"yydebug: state $yystate, error recovery discards \",",
    "            \"token $yychar ($yys)\\n\";",
    "    }",
    "#endif",
    "    $yychar = -1;",
    "    next yyloop;",
    "  }",
    "0;",
    "} # yy_err_recover",
    "",
    "sub yyparse",
    "{",
    "#ifdef YYDEBUG",
    "  if ($yys = $ENV{'YYDEBUG'})",
    "  {",
    "    $yydebug = int($1) if $yys =~ /^(\\d)/;",
    "  }",
    "#endif",
    "",
    "  $yynerrs = 0;",
    "  $yyerrflag = 0;",
    "  $yychar = (-1);",
    "",
    "  $yyssp = 0;",
    "  $yyvsp = 0;",
    "  $yyss[$yyssp] = $yystate = 0;",
    "",
    "yyloop: while(1)",
    "  {",
    "    yyreduce: {",
    "      last yyreduce if ($yyn = $yydefred[$yystate]);",
    "      if ($yychar < 0)",
    "      {",
    "        if (($yychar = &yylex) < 0) { $yychar = 0; }",
    "#if YYDEBUG",
    "        if ($yydebug)",
    "        {",
    "          $yys = '';",
    "          if ($yychar <= $#yyname) { $yys = $yyname[$yychar]; }",
    "          if (!$yys) { $yys = 'illegal-symbol'; };",
    "          print \"yydebug: state $yystate, reading $yychar ($yys)\\n\";",
    "        }",
    "#endif",
    "      }",
    "      if (($yyn = $yysindex[$yystate]) && ($yyn += $yychar) >= 0 &&",
    "              $yycheck[$yyn] == $yychar)",
    "      {",
    "#if YYDEBUG",
    "        print \"yydebug: state $yystate, shifting to state \",",
    "              $yytable[$yyn], \"\\n\"  if $yydebug;",
    "#endif",
    "        $yyss[++$yyssp] = $yystate = $yytable[$yyn];",
    "        $yyvs[++$yyvsp] = $yylval;",
    "        $yychar = (-1);",
    "        --$yyerrflag if $yyerrflag > 0;",
    "        next yyloop;",
    "      }",
    "      if (($yyn = $yyrindex[$yystate]) && ($yyn += $yychar) >= 0 &&",
    "            $yycheck[$yyn] == $yychar)",
    "      {",
    "        $yyn = $yytable[$yyn];",
    "        last yyreduce;",
    "      }",
    "      if (! $yyerrflag) {",
    "        &yyerror('syntax error');",
    "        ++$yynerrs;",
    "      }",
    "      return(1) if &yy_err_recover;",
    "    } # yyreduce",
    "#if YYDEBUG",
    "    print \"yydebug: state $yystate, reducing by rule \",",
    "          \"$yyn ($yyrule[$yyn])\\n\"  if $yydebug;",
    "#endif",
    "    $yym = $yylen[$yyn];",
    "    $yyval = $yyvs[$yyvsp+1-$yym];",
    "    switch:",
    "    {",
    (char *) NULL
};

static char *python_body[] =
{
    "def YYERROR() :",
    "  yynerrs=yynerrs+1",
    "  yy_err_recover()",
    "",
    "def yy_err_recover() :",
    "  if yyerrflag < 3 :",
    "    yyerrflag = 3",
    "    while 1 :",
    "      yyn = yysindex[yyss[yyssp]]",
    "      if yyn :",
    "        yyn = yyn + YYERRCODE",
    "        if yyn >= 0 and yycheck[yyn] == YYERRCODE :",
    "          yystate = yytable[yyn]",
    "          yyssp=yyssp+1",
    "          yyss.append( yystate )",
    "          yyvsp=yyvsp+1",
    "          yyvs.append( yylval )",
    "          return 2 #next yyloop;",
    "        else :",
    "          if yyssp <= 0 :",
    "            return 1",
    "          yyssp=yyssp-1",
    "          yyss.pop()",
    "          yyvsp=yyvsp-1",
    "          yyvs.pop()",
    "  else :",
    "    if yychar == 0 :",
    "      return 1",
    "    yychar = -1",
    "    return 2 #next yyloop;",
    "  return 0",
    "",
    "def yyparse() :",
    "  yydebug = int( os.environ.get('YYDEBUG','0') )",
    "  yynerrs = 0",
    "  yyerrflag = 0",
    "  yychar = -1",
    "  yyssp = 0",
    "  yyvsp = 0",
    "  yyss[yyssp] = 0",
    "  yystate = 0",
    "  #yyloop:",
    "  while 1 :",
    "    #yyreduce: ",
    "    yyn = yydefred[yystate]",
    "    if not yyn :",
    "      if yychar < 0 :",
    "        (yychar, yylval) = yylex()",
    "        if type( yychar ) is types.StringType:",
    "          yychar = ord( yychar )",
    "        if yychar < 0 :",
    "          yychar = 0",
    "        if yydebug :",
    "          print 'yydebug: state ', yystate, ', reading ', yychar, ' (', yyname[yychar], ')'",
    "      yyn = yysindex[yystate]",
    "      if yyn :",
    "        yyn = yyn + yychar",
    "        if yyn >= 0 and yycheck[yyn] == yychar :",
    "          if yydebug :",
    "            print 'yydebug: state ', yystate, ', shifting to state ', yytable[yyn]",
    "          yystate = yytable[yyn]",
    "          yyssp=yyssp+1",
    "          yyss.append( yytable[yyn] )",
    "          yyvsp=yyvsp+1",
    "          yyvs.append( yylval )",
    "          yychar = -1",
    "          if yyerrflag > 0 :",
    "            --yyerrflag ",
    "          continue",
    "      yyn = yyrindex[yystate]",
    "      if yyn :",
    "        yyn = yyn + yychar",
    "        if yyn >= 0 and yycheck[yyn] == yychar :",
    "          yyn = yytable[yyn]",
    "      elif not yyerrflag :",
    "        try :",
    "          yyerror('syntax error')",
    "        except:"
    "          print 'No yyerror function'",
    "        yynerrs=yynerrs+1",
    "      elif yy_err_recover() == 1 :",
    "        return(1)",
    "      elif yy_err_recover() == 2 :",
    "        yychar = -1",
    "        continue",
    "    # yyreduce",
    "    if yydebug :",
    "      print 'yydebug: state ', yystate, ', reducing by rule ', yyn, ' (', yyrule[yyn], ')'",
    "    yym = yylen[yyn]",
    "    yyval = yyvs[yyvsp+1-yym]",
    "    # switch:",
    (char *) NULL
};

char **body[] = { c_body, perl_body, python_body };

static char *c_trailer[] =
{
    "    }",
    "    yyssp -= yym;",
    "    yystate = *yyssp;",
    "    yyvsp -= yym;",
    "    yym = yylhs[yyn];",
    "    if (yystate == 0 && yym == 0)",
    "    {",
    "#if YYDEBUG",
    "        if (yydebug)",
    "            printf(\"yydebug: after reduction, shifting from state 0 to\\",
    " state %d\\n\", YYFINAL);",
    "#endif",
    "        yystate = YYFINAL;",
    "        *++yyssp = YYFINAL;",
    "        *++yyvsp = yyval;",
    "        if (yychar < 0)",
    "        {",
    "            if ((yychar = yylex()) < 0) yychar = 0;",
    "#if YYDEBUG",
    "            if (yydebug)",
    "            {",
    "                yys = 0;",
    "                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];",
    "                if (!yys) yys = \"illegal-symbol\";",
    "                printf(\"yydebug: state %d, reading %d (%s)\\n\",",
    "                        YYFINAL, yychar, yys);",
    "            }",
    "#endif",
    "        }",
    "        if (yychar == 0) goto yyaccept;",
    "        goto yyloop;",
    "    }",
    "    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&",
    "            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)",
    "        yystate = yytable[yyn];",
    "    else",
    "        yystate = yydgoto[yym];",
    "#if YYDEBUG",
    "    if (yydebug)",
    "        printf(\"yydebug: after reduction, shifting from state %d \\",
    "to state %d\\n\", *yyssp, yystate);",
    "#endif",
    "    if (yyssp >= yyss + yystacksize - 1)",
    "    {",
    "        goto yyoverflow;",
    "    }",
    "    *++yyssp = yystate;",
    "    *++yyvsp = yyval;",
    "    goto yyloop;",
    "yyoverflow:",
    "    yyerror(\"yacc stack overflow\");",
    "yyabort:",
    "    return (1);",
    "yyaccept:",
    "    return (0);",
    "}",
    (char *) NULL
};

static char *perl_trailer[] =
{
    "    } # switch",
    "    $yyssp -= $yym;",
    "    $yystate = $yyss[$yyssp];",
    "    $yyvsp -= $yym;",
    "    $yym = $yylhs[$yyn];",
    "    if ($yystate == 0 && $yym == 0)",
    "    {",
    "#if YYDEBUG",
    "      print \"yydebug: after reduction, shifting from state 0 \",",
    "            \"to state (final) $YYFINAL\\n\" if $yydebug;",
    "#endif",
    "      $yystate = $YYFINAL;",
    "      $yyss[++$yyssp] = $YYFINAL;",
    "      $yyvs[++$yyvsp] = $yyval;",
    "      if ($yychar < 0)",
    "      {",
    "        if (($yychar = &yylex) < 0) { $yychar = 0; }",
    "#if YYDEBUG",
    "        if ($yydebug)",
    "        {",
    "          $yys = '';",
    "          if ($yychar <= $#yyname) { $yys = $yyname[$yychar]; }",
    "          if (!$yys) { $yys = 'illegal-symbol'; }",
    "          print \"yydebug: state (final) $YYFINAL, reading $yychar ($yys)\\n\";",
    "        }",
    "#endif",
    "      }",
    "      return(0) if $yychar == 0;",
    "      next yyloop;",
    "    }",
    "    if (($yyn = $yygindex[$yym]) && ($yyn += $yystate) >= 0 &&",
    "        $yyn <= $#yycheck && $yycheck[$yyn] == $yystate)",
    "    {",
    "        $yystate = $yytable[$yyn];",
    "    } else {",
    "        $yystate = $yydgoto[$yym];",
    "    }",
    "#if YYDEBUG",
    "    print \"yydebug: after reduction, shifting from state \",",
    "        \"$yyss[$yyssp] to state $yystate\\n\" if $yydebug;",
    "#endif",
    "    $yyss[++$yyssp] = $yystate;",
    "    $yyvs[++$yyvsp] = $yyval;",
    "  } # yyloop",
    "} # yyparse",
    (char *) NULL
};

static char *python_trailer[] =
{
    "    # switch",
    "    yyssp = yyssp - yym",
    "    yyss[-yym:] = []",
    "    yystate = yyss[yyssp]",
    "    yyvsp = yyvsp - yym",
    "    yyvs[-yym:] = []",
    "    yym = yylhs[yyn]",
    "    if yystate == 0 and yym == 0 :",
    "      if yydebug :",
    "        print 'yydebug: after reduction, shifting from state 0 to (final) state ', YYFINAL",
    "      yystate = YYFINAL",
    "      yyssp=yyssp+1",
    "      yyss.append( YYFINAL )",
    "      yyvsp=yyvsp+1",
    "      yyvs.append( yyval )",
    "      if yychar < 0 :",
    "        (yychar, yylval) = yylex()",
    "        if type( yychar ) is types.StringType :",
    "          yychar = ord( yychar )",
    "        if yychar < 0 :",
    "          yychar = 0",
    "        if yydebug :",
    "          print 'yydebug: state (final) ', YYFINAL, 'reading ', yychar",
    "      if yychar == 0:",
    "        return(0)",
    "      continue",
    "    yyn = yygindex[yym]",
    "    if yyn :",
    "      yyn = yyn + yystate",
    "      if yyn >= 0 and yyn <= (len(yycheck)-1) and yycheck[yyn] == yystate :",
    "        yystate = yytable[yyn]",
    "      else :",
    "        yystate = yydgoto[yym]",
    "    else :",
    "      yystate = yydgoto[yym]",
    "    if yydebug :",
    "      print 'yydebug: after reduction, shifting from state ', yyss[yyssp], ' to state ', yystate",
    "    yyssp=yyssp+1",
    "    yyss.append( yystate )",
    "    yyvsp=yyvsp+1",
    "    yyvs.append( yyval )",
    "  # yyloop",
    "# yyparse",
    (char *) NULL
};

char **trailer[] = { c_trailer, perl_trailer, python_trailer };

#if __STDC__
static char *add_prefixes(char *old_str, char *new_str)
#else
static char *add_prefixes(old_str, new_str)
char *old_str;
char *new_str;
#endif
{
    register char *from = old_str;
    register char *to = new_str;
    register char *p;

    while (*from) {
	if (*from == 'Y' && *(from + 1) == 'Y') {
	    from += 2;
	    p = define_prefix;
	    while (*to++ = *p++)
		/* void */ ;
	    to--;
	}
	else if (*from == 'y' && *(from + 1) == 'y') {
	    from += 2;
	    p = symbol_prefix;
	    while (*to++ = *p++)
		/* void */ ;
	    to--;
	}
	else {
	    *to++ = *from++;
	}
    }

    *to = *from;
    
    return new_str;
}

#if __STDC__
void write_section(char **section[])
#else
void write_section(section)
char **section[];
#endif
{
    register int i;
    register FILE *fp;
    register char **sec = section[(int) language];

    if (sec != (char **) NULL)
    {
	fp = code_file;
	if (prefix_changed)
	{
	    char buf[BUFSIZ];

	    for (i = 0; sec[i]; ++i)
	    {
		++outline;
		fprintf(fp, "%s\n", add_prefixes(sec[i], buf));
	    }
	}
	else
	{
	    for (i = 0; sec[i]; ++i)
	    {
		++outline;
		fprintf(fp, "%s\n", sec[i]);
	    }
	}
    }
}
