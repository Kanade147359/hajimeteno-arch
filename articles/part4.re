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
- 
- 

+
+
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

2. GPUドライバのインストール

ゲーム


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
 2004年のゲームなので
 まず、wineをインストールしましょう。

 //cmd{
 sudo pacman -S wine
 //}

 動きました! 東方永夜抄の解像度は640×480で解像度を変更するオプションは用意されていないので1980×1080で動かすとウィンドウが小さいです。
 しかし、BGMもちゃんと流れて、操作も問題ありません。文字の表示も問題ないようです。

 東方永夜抄では問題ありませんでしたが、ソフトによっては日本語が上手く表示されない場合があります。その際は@<b>{winetricks}でフォントを追加でインストールしましょう。


## 画像編集がしたい(Gimp)

Adobe Photoshopは
しかし、Adobe

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

== セキュリティ専門家になる!

Linuxにはセキュリティ研究者向けに作られたディストリビューションが複数あります。代表的なものは@<b>{Kali Linux}ですね。
Arch Linuxの派生ディストリビューションとして@<b>{BlackArch Linux}というものがあり、blackarchリポジトリを有効にすることで
素のArch LinuxでもBlackArch向けのパッケージを参照できるようになります。

以下の手順を踏んで用意されているstrap.shを実行します。

//cmd{

$ curl -O https://blackarch.org/strap.sh ← strap.shのインストール curlがなければpacmanでインストール

$ echo 26849980b35a42e6e192c6d9ed8c46f0d6d06047 strap.sh | sha1sum -c ← SHA1で検証

$ chmod +x strap.sh ← 実行権を追加

$ sudo ./strap.sh ← rootで実行
//}

終わったらシステムアップデートを行います。


