# Arch Laptopを普段使いする

前章ではplasma desktopと日本語入力環境を導入しました。また、AURヘルパーを導入し、AURに置いてあるパッケージを参照できるようにしました。
これでArch Laptopをノートパソコンとして普段使いする準備が整いました！あとは各自必要なアプリを入れて使い始めるだけです。
本章ではArch Laptopを更に改造していきます。使用用途ごとに章分けしたので必要に応じて読んでいってください。

## 開発を行う

みなさんコードエディタは何を使っているのでしょうか?
今回はユーザ数が多く私も使っているVitual Studio Code(以下VS Code)をインストールします。
Arch Linux向けのVS Codeは公式のArch LinuxのオープンソースリリースであるCode、プロプライエタリなビルドであるvisual Studio Code、コミュニティのオープンソースリリースであるVSCodiumがあります。
全てOSS版のCodeからビルドされていますが、大きな違いとしてOSS版のVS Code(Code, VSCodium)だとMicrosoftが提供するプロプライエタリな機能が使えないという点があります。
これによりOSS版だとVisual Studio Marketplaceから拡張機能を参照できないため使うことができる拡張機能の種類に制限があります。
例えば"GitHub Copilot"、公式の"Python","Jupyter","C/C++"などの拡張機能、Azure関連の公式の拡張機能などがOSS版では使用できません。
筆者はGitHub Copilotを使用したいためプロプライエタリなVS Codeを使用します。
公式レポジトリにはないため、インストールする際はAURヘルパーを用います。

//emlist[Visual Studio Codeのインストール]{
paru visual-studio-code-bin
//}


参考にCode、VSCodiumのインストール方法も乗せておきます。
どれかしらのVS Codeがインストールしている状態で別のビルドをインストールしようとすると元々入っていたVS Codeは消去されます。

//emlist[Codeのインストール]{
sudo pacman -S code 
//}

//emlist[VSCodiumのインストール]{
paru vscodium
//}

VS Codeで日本語入力を行う際は、3章のGoogle Chromeに行ったものと同様の設定が必要になります。
忘れずに設定をしておきましょう。

## steamのインストール

よくPCでゲームをする方はご存知だと思いますが、Steamは米Valve社が提供しているゲーム配信プラットフォームです。
ゲームの購入とインストールは全てSteam上で行うのでSteamを用意すればすぐにゲームで遊べるようになります。

### multilibリポジトリの有効化

steamはmultilibリポジトリに含まれているため、multilibリポジトリを有効にします。
/etc/pacman.confを開き、[multilib]セクションをアンコメントします。
//emlist[/etc/pacman.confをnanoで開く]{
nano /etc/pacman.conf
//}
//emlist[]{
- #[multilib]
- #Include = /etc/pacman.d/mirrorlist
 
+ [multilib]
+ Include = /etc/pacman.d/mirrorlist
}
multilibリポジトリには64bit環境で32bitアプリを実行するために必要なソフトウェアが含まれています。
steamは一部32ビットのライブラリに依存しています。また、古いゲームとの互換性を保つために32bitのライブラリが必要です。
そのため、steamはmultilibリポジトリにまとめられています。

multilibリポジトリの有効化ができたらsteamをインストールしましょう。

//cmd{
sudo pacman -S steam
//}

steam自体はこれでインストール完了ですが、ゲームをするためにはさらに以下の様な設定を追加する必要があるかもしれません。

1. Microsoftフォントの追加

steamではArialフォントをよく使っているようでWindowsに標準搭載されているフォント、またはそのかわりとなるフォントが必要になります。
paruでWindows11に搭載されているフォントを簡単にインストールができます。

//cmd{
paru ttf-ms-win11-auto
//}

このパッケージは自動的にWindows Enterpriseの評価版を取得してフォントデータだけを抜き出す、というなかなかファンキーなことをやっています。
怖い方はArialのフリー版であるLiberation fontをインストールしましょう。

//cmd{
sudo pacman -S ttf-liberation
//}

2. OpenGLドライバのインストール

32bit版のOpenGL graphics driverを予めインストールしておきます。
使用しているGPUの種類は機種によって異なるのでこのページ(@<href>{})の中から該当のGPUドライバを選んでください。
自分はInterl CPUの内蔵GPUを用いているためlib32-mesaをインストールしておきました。64bit版(mesa)も取り敢えずインストールしておきます。

//cmd{
sudo pacman -S lib32-mesa mesa
//}

今回は自分が元々持っていたVampire Survivorsの動作確認をします。

Windowsでプレイするときと操作は同じです。通常通りにゲームが起動され、

デスクトップにショートカットも作成されます。

# Windows対応ソフトを動かす(東方永夜抄)

 steamではゲームごとに対応しているプラットフォームが決められており、Windowsのみに対応しているゲームは
 それでは
 Windows向けの実行ファイル(.exe)をLinuxで動かすことができるプログラム郡である@<b>{wine}というものがあります。
 wineを用いることで一部のWindows向けの実行ファイルをLinux上で動かすことができます。とてもすごい。
 今回は有名な同人ゲームである「東方永夜抄」というゲームを動かします。
 大人気コンテンツである東方Projectの所謂「原作」と言われる東方Projectの生みの親ZUN氏が作成している弾幕シューティングゲームシリーズの第8作目です。
 2004年のゲームなので公式には現在サポートされているWindowsバージョン(10, 11)には対応していませんが、ちゃんと動きます。
 まず、wineをインストールしましょう。

 //cmd{
 sudo pacman -S wine
 //}

 wineがインストールされるとDolphin上から直接.exeファイルを実行できるようになります。
 インストーラーを実行してみましょう。
 するとWindowsにインストールするときと同様の流れでインストールすることが出来ます。
 インストールが終わる際、Windowsの際と同様にデスクトップにショートカットが作成されます。
 それではショートカットから実行してみましょう。

 動きました! 東方永夜抄の解像度は640×480で解像度を変更するオプションは用意されていないので1980×1080で動かすとウィンドウが小さいです。
 しかし、BGMもちゃんと流れて、操作も問題ありません。文字の表示も問題ないようです。

 東方永夜抄では問題ありませんでしたが、ソフトによっては日本語が上手く表示されない場合があります。その際は@<b>{winetricks}でフォントを追加でインストールしましょう。

//cmd{
sudo pacman -S winetricks
winetricks
//}

winetricksが起動したら"Select the default wineprefix"を選択してください。
"Install font"を選択するフォントを選択する画面に遷移します。
容量に余裕があるのならAll fontsを選んで良いと思います。
インストールが終わったらちゃんと日本語が表示されるか再確認してみてください。

## 画像編集がしたい(Gimp)

Adobe Photoshopは2次元コンピュータグラフィックスを代表するソフトで、画像編集ソフトのデファクトスタンダードとしてグラフィックデザイナーや映像編集者、Webデザイナーなど多くの人が使っています。
しかし、Adobe Photoshopを使うには決して安くないライセンス料を払う必要があり、
GIMPはPhotoshopと互換性がある無料の画像編集ソフトです。
無料でありながらPhotoshopと遜色ない高機能な編集ができ、photoshopのプロジェクト保存形式PSDとの互換性もあります。
使いこなせればPhotoshopで行ったのと大差ない出来の編集ができるようです。
この本の表紙もGIMPで作成しています。
gimpは公式リポジトリに含まれているためpacmanコマンドでインストールできます。

//cmd{
sudo pacman -S gimp
//}

起動してみるとこのような画面になります。
操作感が独特ですが、詳しい使い方は調べると沢山出てきます。

## 3Dモデリングがしたい(Blender)

3Dモデリングをする際、よく@<b>{Blender}という

## 作曲をしよう(Reaper)

みなさん作曲はしたことがあるでしょうか。
高いソフトに高いハードウェアが必要そうで敷居が高いと思ってないでしょうか。
しかし、今どき多くの人がパソコン、スマホを持っている時代、
Linuxで無料で使えるDAWソフトである、Reaperをインストールしてみましょう。
公式リポジトリに用意されているため、pacmanでインストールができます。

//cmd{
sudo pacman -S reaper
//}

これでインストールができます。この一コマンドの入力だけで作曲を始めることができます。

Reaperの詳しい使い方は省略します。DAWソフトは使い方が独特でなれないこともあると思いますが、

Reaperに追加でVitalという無料で使えるシンセサイザプラグインがあります。
Vital一つで理論上Future Baseのような電子音楽を作曲できるすごいやつです。

また、有料ソフトでもStudio One6.5がLinuxにbeta対応したり、
歌声合成ソフトであるSynthesizer VがLinuxに対応していたりと、Windowsでないと作曲ができないという常識はなくなりつつあります。

