set shiftwidth=4
set tabstop=4

command! Norminette w | !clear && norminette %
command! RunC w | !clear && cc % && ./a.out
command! RunCF w | !clear && cc -Wall -Werror -Wextra % && ./a.out

" Activate vim syntax coloring
syntax on
" Set line numbers as visible
set nu
" Set row numbers as visible
set ru
" Allow cursor movement by clicking
set mouse=a
set tabstop=4
" Syntax help
set list
set listchars=
"set listchars+=tab:░\
set listchars+=tab:▓░
set listchars+=trail:·
set listchars+=extends:»
set listchars+=precedes:«
set listchars+=nbsp:⣿

let g:user42 = 'nponchon'
let g:mail42 = 'nponchon@42.com'
