# デスクトップ環境のインストール

前章までで必要最低限のパッケージのインストールをインストールしました。
まず、Wi-fi接続をしていきましょう。NetworkManagerには@<b>{nmcli}というCLIでWi-Fi設定ができるツールが付属しています。
以下のコマンドで近くのWi-Fiネットワークを一覧表示します。

//cmd{
$ nmcli device wifi list
//}

つなぎたいWi-Fiネットワークが見つかったら以下のコマンドで接続します。
@<i>{SSID}と@<i>{password}は各ネットワークのものに置き換えてください。

//cmd{
$ nmcli device wifi connect @<i>{SSID} password @<i>{password}
//}

ここまでできたらネットワーク接続を確認してみます。

//cmd{
ping www.archlinux.jp
//}

この用に設定したWi-fiネットワークは保存され、次再起動した際に自動的につながるようになります。
尚有線が使える環境ならケーブルを指すだけでネットワークに繋がります。

インターネットへの接続を確認したらデスクトップ環境をインストールしていきましょう。
デスクトップ環境は様々な種類がありますが、今回は個人的に好きなKDEをインストールしていきます。

## そもそもデスクトップ環境とは何か

私たちが今まで触ってきた黒い画面にコマンドを打って操作をするUIをCLI(Command Line Interface)といいます。
Linux向けのデスクトップ環境は様々な種類があり、それぞれに特徴があります。
例えば、Ubuntu DesktopはGnomeというデスクトップ環境を採用しています。
余談ですが、Ubuntuには公式フレーバーとしてデスクトップ環境を変えたバージョンのUbuntuが複数配布されています
(KDEを採用したKubuntu、Xfceを採用したXubuntu、LXQtを採用したLubuntuなど)。

今回はKDEというデスクトップ環境をインストールしてArch Laptopを完成させていきましょう。

## インストール

インストールはとても簡単です。pacmanでplasmaパッケージグループをインストールしていきます。


//emlist[Visual Studio Codeのインストール]{
$ sudo pacman -S plasma
//}

パッケージグループとは関連パッケージをまとめたものでグループの中から必要なパッケージを選んでまとめてインストールできるものです。
このコマンドを使うと多くのパッケージの名前が列挙されます。今回は全てインストールするためデフォルトのallで問題ありません。
因みにデスクトップ環境は最低限plasma-desktopをインストールすれば動きます。しかし、ネットワーク設定、サウンド設定など欲しい機能が何もない形だけのGUI環境が出来上がり、どの部分になんのパッケージが必要なのかが分かりにくい(自分の不勉強ですが…)ので
パッケージグループでまとめて入れてしまいます。

インストールができたらディスプレイマネージャのSDDMをインストールしていきます。
ディスプレイマネージャとはGUIのログイン画面を表示してデスクトップ環境を起動するプログラムです。
これ、始めは衝撃だったのですが、ログイン画面とログイン後のデスクトップ環境は独立しています。それぞれ色々な種類があるので自分の好みに合わせて組み合わせて使うことができます。

Plasmaが推奨しており、KDEで設定ができるSDDMを採用します。

//emlist[SDDMのインストール]{
sudo pacman -S sddm
//}

SDDMのサービスを有効化します。

//emlist[起動時SDDMを自動で有効化するよう設定]{
sudo systemctl enable sddm
//}

ここまで設定したら再起動をすれば、デスクトップ環境の導入完了です。
思ったより簡単だったのではないでしょうか

## 端末エミュレータのインストール

無事にデスクトップ環境に入れましたでしょうか。
このWindowsライクな非常にわかりやすいUIがKDEの魅力です。

次に端末エミュレータをインストールしていきます。
macOSやUbuntuでいうterminalアプリのようなものですね。
GUI環境でCLIをエミュレートするアプリです。
Arch Linuxで使うアプリはできるだけpacmanで管理をしたいので
これからもCLI環境を多く使います。
しかし、plasmaパッケージグループには端末エミュレータが含まれていないため、
自分でインストールする必要があります。

今回インストールするのは@<b>{Yakuake}という端末エミュレータです。
Yakuakeはトップダウン型のターミナルで好きなときに指定したキーを押すとこのようにターミナルが垂れ下がるように開くことができる、とても便利な端末エミュレータです。
早速インストールしていきましょう。端末を開いてください。

…@<b>{その端末がないじゃないですか}

安心してください。@<b>{仮想コンソール}を開きます。

### 仮想コンソール

GUI環境であってもコンソール(CLI)を開くことができます。
ctrl+alt+F3を押してください。
するとCLIが開きます。
インストール直後のログインのようにユーザ名とパスワードを入力すると
コンソールに入ることができました。

Linuxには仮想コンソールが複数用意されています。(tty1~tty6)
どの仮想コンソールに入っているかは@<b>{tty}コマンドで確認できます。
//cmd{
tty
//}

KDEの場合、tty1とtty2がplasmaとsddmに使われているので他に使うことができる仮想コンソールはtty3~6です。
今回はtty3に入っていると思います。

仮想コンソールが主に役立つときは緊急時の復旧対応だと思います。
これから負荷の高い使い方をしていくと、メモリ不足などでパソコンがフリーズすることがあるでしょう。
そのときは仮想コンソールに入ることを試してみてください。CLIからrebootしたり、問題のあるプロセスをkillしたりできます。

さて、仮想コンソールに入ったのでpacmanでYakuakemをインストールしましょう。

//cmd{
sudo pacman -S yakuake
//}

インストールが完了したら元のデスクトップ環境に戻りましょう。
Ctrl+Alt+F1で元のデスクトップ画面に戻ることができます。

デスクトップ環境に戻ったらYakuakeを実行してみましょう。左下のメニューでYakuakeと検索すると出てくると思います。
初めて開くときにYakuakeを呼び出すときに使うキーを指定します。初期設定はF12ですが、F12キーを別のアプリでよく用いる人は変える必要があるでしょう。
一度開くと指定したキーでYakuakeが自由に呼び出せるようになります。とても便利ですね。



### 自動起動設定

Yakuakeは裏で動かしておいて、必要に応じて開けるようにしておきたいです。
そのためには再起動時Yakuakeを都度起動する必要があります。
Yakuakeをパソコンの起動時自動で起動してくれるように設定しておきましょう。

KDEシステム設定を開きます。
システムの欄に自動起動というメニューがあります。
右上の追加を押してYakuakeを選びます。

この用に設定をしておくとYakuakeが再起動時自動で呼ばれる用になります。

## KDE Applicationsについて

KDE ApplicationsはKDEによって開発が進められているplasma上で動かすことができるアプリ郡です。
KDE Applicationsは100以上のアプリケーションによって構成されており、エクスプローラや端末エミュレータのような必須級のアプリから麻雀、マインスイーパーのようなゲームまで多種多様なアプリが用意されています。
尚、YakuakeはKDE Applicationsというアプリ郡の中の一つです。

KDE Applicationsから必須級のアプリを3つ入れていきます。ファイルエクスプローラである@<b>{Dolphin}をダウンロードしておきましょう。

//cmd{
sudo pacman -S dolphin
//}

インストールするとWindowsのエクスプローラのようなアイコンが追加された事がわかります。

また、圧縮ファイルの作成、解凍を行うアーカイブマネージャである@<b>{Ark}をインストールしましょう。

//cmd{
sudo pacman -S ark
//}

最後にスクリーンショットを行うためのアプリ、Spectacleをインストールします。

//cmd{
sudo pacman -S spectacle
//}

インストールが終わったらPrintScreenキーを押してみてください。
Spectacleが開くようになっているはずです。
開かない場合は手動で開いて設定を確認してください。

## 日本語環境のインストール

現在は日本語が入力できない環境にあります。また、日本語フォントが入っていないため、日本語がうまく表示されない状態でしょう。
まず、日本語フォントをインストールしていきます。とりあえずGoogleのNotoCJKフォントをインストールしていきます。

//cmd{
sudo pacman -S noto-fonts-cjk
//}

インストールが終わったら日本語が上手く表示される様になるはずです。
この状態になったらシステム設定の「地域と言語」から言語を「日本語」に変えましょう。
言語が日本語に変更されます。フォントに違和感があるかもしれませんが、公式レポジトリ、また後述のAURを含めると様々な日本語フォントが用意されています。
システムのフォントもその中から選ぶことができるため、後に好きなように変更をしましょう。

さて、日本語入力環境のため、インプットメソッドフレームワークである@<b>{Fcitx5}をインストールしていきます。

=== Fcitx5のインストール

入力メソッドをインストールしましょう。

## AURヘルパーのインストール

Arch Linuxには公式リポジトリの他にArch User Repository(以下 AUR)と呼ばれる非公式リポジトリがあります。
この非公式リポジトリにはGoogle ChromeやVisual Studio CodeのようなプロプライエタリなソフトウェアはAURで配布されています。
AURにあるパッケージをインストールするにはそのパッケージのgitリポジトリをクローンして手元でビルドしてからpacmanでインストール、
という簡略化されているとはいえ面倒な手順を踏む必要があります。これらを自動化し、pacmanと同様にAURのパッケージをインストールできるようにしたソフトがAURヘルパーです。
今回はその中でもparuというAURヘルパーを導入します。
paru自体がAURのパッケージとして配布されているため、ちゃんと手順を踏んでビルドしていきます。

まず、必要な開発パッケージをインストールします。

//emlist[base-develのインストール]{
sudo pacman -S base-devel
//}

AURのパッケージはbase-develがある前提でビルド手順が組まれているため、必ずインストールしましょう。

paruのgitリポジトリをクローンします。

//emlist[]{
git clone https://aur.archlinux.org/paru.git
//}

ビルドしてインストールをします。

//emlist[]{
cd paru
makepkg -si
//}

ビルドには時間がかかるので気長に待ちましょう。

ビルドが無事完了したら動作確認をしてみましょう。

//emlist[]{
paru -V
//}

バージョン番号が表示されたらインストール完了です。

## AURパッケージをインストールしてみよう

paruを実際に使ってみましょう。ここではコンソール上でパックマンが遊べるpacman4consoleをインストールしていきます。
以下のようなコマンドでインストールができます。

//emlist[]{
paru pacman4console
//}

パッケージ名が列挙されるのでインストールするパッケージを選びます。今回は一つだけ表示されていると思うので1を入力します。
レビューの表示を迫ってくるのでYを入力。レビューが表示されますがqキーを押すと退出できます。退出するとパッケージのビルドが始まります。







