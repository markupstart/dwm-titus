/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int refresh_rate    = 120;     /* matches dwm's mouse event processing to your monitor's refresh rate for smoother window interactions */
static const unsigned int enable_noborder = 1;      /* toggles noborder feature (0=disabled, 1=enabled) */
static const unsigned int borderpx        = 2;      /* border pixel of windows */
static const unsigned int snap            = 26;     /* snap pixel */
static const int swallowfloating          = 1;      /* 1 means swallow floating windows by default */
static const unsigned int systraypinning  = 0;      /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;      /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 5;      /* systray spacing */
static const int systraypinningfailfirst  = 1;      /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1;      /* 0 means no systray */
static const int showbar                  = 1;      /* 0 means no bar */
static const int topbar                   = 1;      /* 0 means bottom bar */
#define ICONSIZE                            17      /* icon size */
#define ICONSPACING                         5       /* space between icon and title */
#define SHOWWINICON                         1       /* 0 means no winicon */
static const char *fonts[]                = { "MesloLGS Nerd Font Mono:size=16", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true"  };
static const char normbordercolor[]       = "#3B4252";
static const char normbgcolor[]           = "#2E3440";
static const char normfgcolor[]           = "#D8DEE9";
static const char selbordercolor[]        = "#ffA500";
static const char selbgcolor[]            = "#434C5E";
static const char selfgcolor[]            = "#ECEFF4";

static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel] =  { selfgcolor,  selbgcolor,  selbordercolor },
};

static const char *const autostart[] = {
  "xset", "s", "off", NULL,
  "xset", "s", "noblank", NULL,
  "xset", "-dpms", NULL,
  "dbus-update-activation-environment", "--systemd", "--all", NULL,
  "lxpolkit", NULL,
  "flameshot", NULL,
  "dunst", NULL,
  "picom", "--animations", "-b", NULL,
  "feh", "--bg-scale", "/home/mark/wall2.jpg", NULL,
  "/home/mark/status2", NULL,
  "nextcloud", NULL,
  NULL /* terminate */
};

/* tagging */
static const char *tags[] = { "🌐","📁","","💬","","📷","","📜","🪶" };

static const char ptagf[] = "[%s %s]";  /* format of a tag label */
static const char etagf[] = "[%s]";     /* format of an empty tag */
static const int lcaselbl = 0;          /* 1 means make tag label lowercase */

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "kitty",   NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.30; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "|C|",      centeredmaster },
};

/* key definitions */
#define PrintScreenDWM	    0x0000ff61
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define STATUSBAR "dwmblocks"
/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *browsercmd[]  = { "firefox", NULL };
static const char *discordcmd[]  = { "discord", NULL };
static const char *gamingcmd[]  = { "lutris", NULL };
static const char *recordingcmd[]  = { "obs", NULL };
static const char *thunarcmd[]  = { "thunar", NULL };
static const char *cmdprintscreen[]  = { "flameshot", "full", NULL };

static Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_p,          spawn,                {.v = dmenucmd } },
	{ MODKEY, 		 				XK_a,          spawn,                {.v = termcmd } },
	{ MODKEY,		     		    XK_f,          spawn,   	         {.v = browsercmd } },
	{ MODKEY,			 		    XK_d,          spawn, 	             {.v = discordcmd } },
	{ MODKEY, 			 			XK_g,          spawn,   	         {.v = gamingcmd } },
	{ MODKEY,			 			XK_o,          spawn,   	         {.v = recordingcmd } },
	{ MODKEY,  			 			XK_t,          spawn, 	             {.v = thunarcmd } },
	{ 0,    	          PrintScreenDWM,      	   spawn,                {.v = cmdprintscreen } },
	{ 0,                            0x1008ff12,    spawn,                  SHCMD ("amixer sset Master $(amixer get Master | grep -q '\\[on\\]' && echo 'mute' || echo 'unmute')")}, // toggle mute/unmute
	{ 0,                            0x1008ff13,    spawn,                  SHCMD ("amixer sset Master 5%+ unmute")}, // unmute volume
	{ MODKEY,                       XK_b,          togglebar,              {0} },
	{ MODKEY,                       XK_k,          focusstack,             {.i = +1 } },
	{ MODKEY,                       XK_j,          focusstack,             {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_k,          movestack,              {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_j,          movestack,              {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,          incnmaster,             {.i = +1 } }, // decrease the number of clients in the master area
	{ MODKEY|ShiftMask,             XK_d,          incnmaster,             {.i = -1 } }, // increase the number of clients in the master area
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} }, // decrease the size of the master area compared to the stack area(s)
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} }, // increase the size of the master area compared to the stack area(s)
	{ MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} }, // increase size respective to other windows within the same area
	{ MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} }, // decrease client size respective to other windows within the same area
	{ MODKEY|ShiftMask,             XK_o,          setcfact,               {.f =  0.00} }, // reset client area
	{ MODKEY,                       XK_Return,     zoom,                   {0} }, // moves the currently focused window to/from the master area (for tiled layouts)
	{ MODKEY,                       XK_Tab,        view,                   {0} }, // view last focused tag
	{ MODKEY, 		                XK_c,          killclient,             {0} },
	{ MODKEY,                       XK_u,          setlayout,              {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_f,          fullscreen,             {0} }, // toggles fullscreen for the currently selected client
	{ MODKEY|ShiftMask,             XK_space,      togglefloating,         {0} },
	{ MODKEY|ShiftMask,             XK_b,          togglefakefullscreen,   {0} }, // toggles "fake" fullscreen for the selected window
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } }, // view all tags on the current monitor
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } }, // focus on the previous monitor, if any
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } }, // focus on the next monitor, if any
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } }, // tag previous monitor
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } }, // tag next monitor
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} }, // exit dwm
	{ MODKEY|ControlMask,           XK_q,          spawn,                  SHCMD ("$HOME/.config/rofi/powermenu.sh")}, // exit dwm
	{ MODKEY|ControlMask|ShiftMask, XK_r,          spawn,                  SHCMD("systemctl reboot")}, // reboot system
	{ MODKEY|ControlMask|ShiftMask, XK_s,          spawn,                  SHCMD("systemctl suspend")}, // suspend system
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 2} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};