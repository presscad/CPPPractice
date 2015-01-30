"********************************************
"  _vimrc/_gvimrc for windows
"  BY Douboer
"********************************************

"Cygwin相关设置
set nocompatible
set backspace=indent,eol,start

"
" echo "loading _vimrc ... "
"


"set nocompatible
source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim
behave mswin


set diffexpr=MyDiff()
function MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  silent execute '!"C:\Vim\vim70\diff" -a' . opt . v:fname_in . ' ' . v:fname_new . ' > ' . v:fname_out
endfunction




"
" 不同中文编码显示
" 同时支持GBK和UTF-8编码
"
"set fileencoding=gb18030
"set fileencodings=utf-8,gb18030,utf-16,big5
"set fileencodings=ucs-bom,utf-8,cp936
set fileencoding=utf-8
"set encoding=cp936 
set encoding=utf-8


"
" 设置字体
"
set guifont=Lucida_Console:h12:cANSI
"set guifont=courier_new:h15


"
" 启动最大化, 设置颜色方案
"
"winsize 1920 1048
au GUIEnter * simalt ~x
colorscheme darkblue

"set lines=62 columns=239

"
"自动缩进
"
set autoindent


"
" 设置tab制表符为4个空格
"
set ts=4
set expandtab
set shiftwidth=4
set cinoptions=>4,e0,n0,f0,{0,}0,^0,:s,=s,l0,gs,hs,ps,ts,+s,c3,C0,(2s,us,
                          \U0,w0,m0,j0,)20,*30
"
"set cindent
"


"
" 展开显示文件类型菜单
"
let do_syntax_sel_menu = 1 | runtime! synmenu.vim | aunmenu &Syntax.&Show\ filetypes\ in\ menu


"
" 设置语法
"
"if &filetype != 'javacc'
"    setlocal filetype=javacc
"endif
"set syntax=javacc
"cal SetSyn("cpp")
"cal SetSyn("vb")
"cal SetSyn("perl")
"cal SetSyn("awk")


"
" 备份文件放在指定目录
"
set backupdir=C:\tmp

if has("vms")
  set nobackup  " do not keep a backup file, use versions instead


"
" 没有警告音和视觉警告
"
set vb t_vb=


"
" 禁用swf交换文件
"
setlocal noswapfile


"
" 显示行号
"
set number


"
" 隐藏工具条
"
" see :help 'guioptions'
"
set guioptions-=T
"set guioptions-=m


"
" 状态条，显示字节数，列数，行数，当前行等信息
"
set statusline=%F%m%r%h%w\ [FORMAT=%{&ff}]\ [TYPE=%Y]\ [ASCII=\%03.3b]\ [HEX=\%02.2B]\ [POS=%04l,%04v][%p%%]\ [LEN=%L]
set laststatus=2 " always show the status line


"
"auto-comments for // and /* */
"setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,://
"
"disable auto-comments for //
"setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*,mb:*,ex:*/,f://
"
"disable auto-comments for // and /* */
"
"setlocal comments=sO:*\ -,mO:*\ \ ,exO:*/,s1:/*
setlocal comments=""
filetype plugin indent on
set completeopt=longest,menu


set filetype=python
au BufNewFile,BufRead *.py,*.pyw setf python