#include <X11/XF86keysym.h>
/* appearance */
static const int swallowfloating    = 1;        /* 1 means swallow floating windows by default */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 6;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus-font:size=14" };
static const char dmenufont[]       = "terminus-font:size=16";
static const char normfg[]       = "#BBBBBB";
static const char normbg[]       = "#000000";
static const char normborder[]       = "#444444";
static const char selfg[]       = "#BBBBBB";
static const char selbg[]       = "#222222";
static const char selborder[]       = "#BBBBBB";
static const char hidfg[]       = "#555555";
static const char hidbg[]       = "#000000";
static const char hidborder[]       = "#000000";


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { normfg, normbg, normborder },
	[SchemeSel]  = { selfg, selbg,  selborder  },
	[SchemeHid]  = { hidfg,  hidbg, hidborder  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "st-256color",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbg, "-nf", normfg, "-sb", selbg, "-sf", selfg, NULL };
static const char *layoutmenu_cmd = "dwm/layoutmenu.sh";
static const char *termcmd[] 	= { "st", NULL };
static const char term[]  	= "st";

static const char *browser[]  	= { "chromium", NULL };
static const char *discord[]  	= { "discord", NULL };
static const char *steam[] 	= { "steam", NULL };
static const char *pcmanfm[] 	= { "pcmanfm", NULL };
static const char *rss[]  	= { term, "newsboat", NULL };
static const char *ncmpcpp[]  	= { term, "ncmpcpp", NULL };
static const char *ranger[]  	= { term, "ranger", NULL };
static const char *pulsemixer[]	= { term, "pulsemixer", NULL };

static const char *volup[] 	= { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "+5%", NULL };
static const char *voldown[]  	= { "pactl", "set-sink-volume", "@DEFAULT_SINK@", "-5%", NULL };
static const char *volmute[]  	= { "pactl", "set-sink-mute", "@DEFAULT_SINK@", "toggle", NULL };
static const char *micmute[]  	= { "pactl", "set-source-mute", "@DEFAULT_SOURCE@", "toggle", NULL };
static const char *xbacklightup[]  	= { "xbacklight", "-dec", "5", NULL };
static const char *xbacklightdown[]  	= { "xbacklight", "-inc", "5", NULL };

static const char *play_pause[]	= { "mpc", "toggle", NULL };
static const char *prev_song[]  = { "mpc", "prev", NULL };
static const char *next_song[]  = { "mpc", "next", NULL };

static const char *scrot[]  	= { "scrot", NULL };


static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,          spawn,                  {.v = dmenucmd } },
        { MODKEY,    		        XK_a,          spawn,                  {.v = termcmd } },
        { MODKEY,    		        XK_s,          spawn,                  {.v = browser } },
	{ MODKEY|ShiftMask,             XK_f,          spawn,                  {.v = rss } },
	{ MODKEY|ShiftMask,             XK_a,          spawn,                  {.v = ranger } },
	{ MODKEY|ControlMask,           XK_a,          spawn,                  {.v = pcmanfm } },
	{ MODKEY,	                XK_g,          spawn,                  {.v = discord } },
	{ MODKEY|ShiftMask,             XK_g,          spawn,                  {.v = steam } },
	{ MODKEY,	                XK_f,          spawn,                  {.v = ncmpcpp } },
	{ MODKEY,	                XK_o,          spawn,                  {.v = scrot } },


	{ 0, 				XF86XK_AudioRaiseVolume, spawn,        {.v = volup } } ,
	{ 0,    			XF86XK_AudioLowerVolume, spawn,        {.v = voldown } },
	{ 0,		 	        XF86XK_AudioMute,      	 spawn,        {.v = volmute } },
	{ 0,		 	        XF86XK_AudioMicMute,      	 spawn,        {.v = micmute } },
	{ 0,		 	        XF86XK_MonBrightnessDown,      	 spawn,        {.v = xbacklightup } },
	{ 0,		 	        XF86XK_MonBrightnessUp,      	 spawn,        {.v = xbacklightdown } },

	{ ControlMask, 			XK_Right,      spawn,                  {.v = volup } } ,
	{ ControlMask,    		XK_Left,       spawn,                  {.v = voldown } },
	{ ControlMask,		        XK_Down,       spawn,                  {.v = volmute } },
	{ ControlMask|ShiftMask,        XK_Down,       spawn,                  {.v = pulsemixer } },

	{ ControlMask,	       		XK_Up,         spawn,                  {.v = play_pause } } ,
	{ ControlMask|ShiftMask,        XK_Left,       spawn,                  {.v = prev_song } }, 
	{ ControlMask|ShiftMask,	XK_Right,      spawn,                  {.v = next_song } }, 


	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstackvis,  {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstackvis,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      focusstackhid,  {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      focusstackhid,  {.i = -1 } },
	{ MODKEY,                       XK_w,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_q,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY, 	             XK_z,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_y,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,             XK_space,  togglefloating, {0} },
	{ MODKEY,	             XK_x,      togglefullscr,  {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,                       XK_v,      show,           {0} },
	{ MODKEY,                       XK_c,      hide,           {0} },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        layoutmenu,     {0} },

	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
	{ ClkWinTitle,          0,              Button3,        zoom,           {0} },

	{ ClkStatusText,        0,                   Button1,        spawn,          {.v = termcmd } },
	{ ClkStatusText,        0,                   Button2,        togglebar,      {0} },
	{ ClkStatusText,        0,                   Button3,        spawn,          {.v = dmenucmd } },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },

	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            0,         Button2,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button2,        toggletag,      {0} },
};

