%token ID MONTH DAY MERIDIAN NUMBER UNIT MUNIT SUNIT ZONE DAYZONE AGO
%{
# 	Steven M. Bellovin (unc!smb)
#	Dept. of Computer Science
#	University of North Carolina at Chapel Hill
#	@(#)getdate.y	2.13	9/16/86
#
#	Richard J. Ohnemus (rick@IMD.Sterling.COM)
#	(Where do I work??? I'm not even sure who I am! 8-{)
#	04/24/92  converted to PERL.
#	07/06/92  New date format (MONTH NUMBER NUMBER ':' NUMBER ':' NUMBER)
#		  suggested by Raphael Manfredi <ram@eiffel.com>.
#	07/08/92  Fixed table search in &lookup.
#		  Call &localtime with correct value in &monthadd.
#	10/08/92  Numeric values starting with pattern '0+[89]' interpretted
#		  correctly.
#		  Corrected European Western and Eastern time offsets.
#		  Borrowed code from timelocal.pl to determine timezone offset
#		  from GMT.
#	10/10/92  Handle time zone offsets correctly (sign was reversed).
#		  Set global time zone variable ('ourzone') correctly.
#	12/24/92  Fixed problem with military time zones.

package getdate;

$AM = 1;
$PM = 2;
$DAYLIGHT = 1;
$STANDARD = 2;
$MAYBE = 3;

@mdays = (31, 0, 31,  30, 31, 30,  31, 31, 30,  31, 30, 31);
$epoch = 1970;
$daysec = 24 * 60 * 60;
%}

%%
timedate: 		/* empty */
	| timedate item
	;

item:	tspec =
		{
		    $timeflag++;
		}
	| zone =
		{
		    $zoneflag++;
		}
	| dtspec =
		{
		    $dateflag++;
		}
	| dyspec =
		{
		    $dayflag++;
		}
	| rspec =
		{
		    $relflag++;
		}
	| nspec
	;

nspec:	NUMBER =
		{
		    if ($timeflag && $dateflag && !$relflag) {
			$year = $1;
		    }
		    else {
			$timeflag++;
			$hh = int($1 / 100);
			$mm = $1 % 100;
			$ss = 0;
			$merid = 24;
		    }
		}
	;

tspec:	NUMBER MERIDIAN =
		{
		    $hh = $1;
		    $mm = 0;
		    $ss = 0;
		    $merid = $2;
		}
	| NUMBER ':' NUMBER =
		{
		    $hh = $1;
		    $mm = $3;
		    $merid = 24;
		}
	| NUMBER ':' NUMBER MERIDIAN =
		{
		    $hh = $1;
		    $mm = $3;
		    $merid = $4;
		}
	| NUMBER ':' NUMBER NUMBER =
		{
		    $hh = $1;
		    $mm = $3;
		    $merid = 24;
		    $daylight = $STANDARD;
		    $ourzone = -($4 % 100 + 60 * int($4 / 100));
		}
	| NUMBER ':' NUMBER ':' NUMBER =
		{
		    $hh = $1;
		    $mm = $3;
		    $ss = $5;
		    $merid = 24;
		}
	| NUMBER ':' NUMBER ':' NUMBER MERIDIAN =
		{
		    $hh = $1;
		    $mm = $3;
		    $ss = $5;
		    $merid = $6;
		}
	| NUMBER ':' NUMBER ':' NUMBER NUMBER =
		{
		    $hh = $1;
		    $mm = $3;
		    $ss = $5;
		    $merid = 24;
		    $daylight = $STANDARD;
		    $ourzone = -($6 % 100 + 60 * int($6 / 100));
		}
	;

zone:	ZONE =
		{
		    $ourzone = $1;
		    $daylight = $STANDARD;
		}
	| DAYZONE =
		{
		    $ourzone = $1;
		    $daylight = $DAYLIGHT;
		}
	;

dyspec:	DAY =
		{
		    $dayord = 1;
		    $dayreq = $1;
		}
	| DAY ',' =
		{
		    $dayord = 1;
		    $dayreq = $1;
		}
	| NUMBER DAY =
		{
		    $dayord = $1;
		    $dayreq = $2;
		}
	;

dtspec:	NUMBER '/' NUMBER =
		{
		    $month = $1;
		    $day = $3;
		}
	| NUMBER '/' NUMBER '/' NUMBER =
		{
		    /*
		     * HACK ALERT!!!!
		     * The 1000 is a magic number to attempt to force
		     * use of 4 digit years if year/month/day can be
		     * parsed. This was only done for backwards
		     * compatibility in rh.
		     */
		    if ($1 > 1000) {
			$year = $1;
			$month = $3;
			$day = $5;
		    }
		    else {
			$month = $1;
			$day = $3;
			$year = $5;
		    }
		}
	| MONTH NUMBER =
		{
		    $month = $1;
		    $day = $2;
		}
	| MONTH NUMBER ',' NUMBER =
		{
		    $month = $1;
		    $day = $2;
		    $year = $4;
		}
	| MONTH NUMBER NUMBER ':' NUMBER =
		{
		    $month = $1;
		    $day = $2;
		    $hh = $3;
		    $mm = $5;
		    $merid = 24;
		    $timeflag++;
		}
	| MONTH NUMBER NUMBER ':' NUMBER ':' NUMBER =
		{
		    $month = $1;
		    $day = $2;
		    $hh = $3;
		    $mm = $5;
		    $ss = $7;
		    $merid = 24;
		    $timeflag++;
		}
	| MONTH NUMBER NUMBER =
		{
		    $month = $1;
		    $day = $2;
		    $year = $3;
		}
	| NUMBER MONTH =
		{
		    $month = $2;
		    $day = $1;
		}
	| NUMBER MONTH NUMBER =
		{
		    $month = $2;
		    $day = $1;
		    $year = $3;
		}
	;

rspec:	NUMBER UNIT =
		{
		    $relsec += 60 * $1 * $2;
		}
	| NUMBER MUNIT =
		{
		    $relmonth += $1 * $2;
		}
	| NUMBER SUNIT =
		{
		    $relsec += $1;
		}
	| UNIT =
		{
		    $relsec +=  60 * $1;
		}
	| MUNIT =
		{
		    $relmonth += $1;
		}
	| SUNIT =
		{
		    $relsec++;
		}
	| rspec AGO =
		{
		    $relsec = -$relsec;
		    $relmonth = -$relmonth;
		}
	;
%%

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
