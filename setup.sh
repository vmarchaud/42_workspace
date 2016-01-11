curl http://www.iterm2.com/nightly/iTerm2-2_9_20160108-nightly.zip > ~/Downloads/Iterm.zip
open ~/Downloads/Iterm.zip
curl -L http://install.ohmyz.sh | sh
curl https://raw.githubusercontent.com/reversTeam/Sublivim/master/installer.sh | sh 
curl https://raw.githubusercontent.com/sickill/vim-monokai/master/colors/monokai.vim > ~/.vim/colors/monokai.vim
sed -i -- 's/molokai/monokai/g' ~/.vimrc
curl https://raw.githubusercontent.com/oskarkrawczyk/honukai-iterm/master/honukai.zsh-theme > ~/.oh-my-zsh/themes/honukai.zsh-theme
echo "sed -i -- 's/robyrussell/honukai/g' ~/.zshrc"
echo "source ~/.zshrc"
curl https://raw.githubusercontent.com/oskarkrawczyk/honukai-iterm/master/honukai.itermcolors > ~/Downloads/honukai.itermcolors
open ~/Downloads/iTerm.app/ 
