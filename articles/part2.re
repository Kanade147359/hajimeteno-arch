= Arch Linuxをインストールする

まず公式HPのインストールガイドに沿ってArch Linuxをインストールします。
ここでは最低限起動する状態を目指していきます。


== インストールメディアの作成

まず、インストールメディアを作成します。USBメモリを用意してください。
DVDドライブのあるノートパソコンであればDVDに焼いても問題ありません。
今回はインストールディスクを作成する二種類の方法を紹介します。

1. rufusを使う(Windowsユーザ向け)

rufusはブート可能なUSBドライブを簡単に作ることができるWindowsソフトです。
rufusのダウンロードページ(https://rufus.ie/ja/)からダウンロードしてください。64bitパソコンを使っている人が殆どかと思いますので
rufus-4.4_x86.exeのようにx86とついているリンクを使ってください。

同じようなソフトでbalenaEtherというものがあります。こちらはmacOSに対応しているのでmacの方はこちらを使うのが良いでしょう。
使い方の説明は省略します。rufusよりUIは分かりやすいと思います。
動作確認はしていませんが、ChromoOSを使っている方もbalenaEtherのLinux版を使うことができるようです。
しかし、導入が面倒かもしれません。

2. Ventoyを使う

Ventoyは複数のisoファイルをブート可能なUSBドライブを作ることができるツールです。
Ventoyは一度Ventoyデバイスを作ってしまえばあとはisoファイルのコピペでインストールメディアを作成できるようになります。
こちらもWindowsで作る方法のみ参考として紹介しておきます。


ChromeOSで作る方法もあるようですので、どうしてもWindows環境がない方は試してみてください。

== USBからパソコンを起動する

前節でインストールディスクを作成しました。
それでは作成したインストールディスクをパソコンから起動します。
まずBIOS設定画面に入りましょう。
パソコンを起動する際、起動画面(メーカーの名前が表示されている際)に特定のキーを押すとBIOS設定画面に遷移します。
この特定のキーはF2キーだったりDelキーだったりしますがメーカーによって異なるので各自調べてください。
情報がなかったらとりあえずF2かDelキーを試してみると大抵入ることができると思います。

BIOS画面に入ったらブート設定を変更します。ブート順序をUSBを1位に変更します。

変更したら設定変更を保存して再起動します。この際、インストールディスクを挿しておいてください。

起動してこのような画面が表示されたら成功です。一番上の項目(Arch Linux install medium)を選択してください。
Arch Linuxのインストーラーが起動します。

このような画面になったらインストーラーの起動に成功しています。
もしブートに失敗した場合はrufusでインストールディスクをMBRパーティションにして作り直してみてください。
BIOS

== キーレイアウトの選択 起動モードの確認

まず、キーレイアウトを設定する必要があります。初期状態ではUSキーボードがセットされています。
もし日本語キーボードを使用している場合は以下のようなコマンドでキーレイアウトを変更します。



起動モードの確認を行う必要があります。起動モードによってインストール手順が異なる箇所があるので
必ず確認しましょう。

次のコマンドの出力を確認してください。
//emlist[]{ 
ls /sys/firmware/efi/efivars
//}

このコマンドの出力結果が正しく表示されている場合はUEFIモードで起動しています。
一方、このコマンドの出力がNo such file or directoryのようなエラー文であった場合、BIOSモードで起動しています。

比較的新しいPC(だいたい2010年以降に販売されていたPC)の場合、UEFIモードで起動できると思いますので、
BIOSモードで起動している場合はBIOS設定を確認してみてください。もし起動モードの設定を見つけたら
起動モードをLegacyモードからUEFIモードに変換するとUEFIモードで開くことができます。


== Wifiにつなげる


Arch Linuxを触ったことがある人でも仮想マシンにインストールする過程では発生しない操作なのでやったことのない人が多いのではないでしょうか。
Wifi設定は@<b>{iwd}というソフトを用いて行います。

まずiwdの対話型プロンプトに入ります。

//emlist[]{
# iwctl
//}

以下のような表示になればOKです。

//emlist[]{
[iwd]#
//}

対話型プロンプトから出て、ネットワーク疎通を確認しましょう。
//emlist[]{ 
[iwd]# exit
# ping www.archlinux.jp
//}

ネットワークに繋がっていることを確認したら次に進みましょう。

== パーティション分割〜マウントまで

次にインストールするドライブのパーティション分割をし、各パーティションをフォーマットします。
パーティションとはHDDやSSDのようなストレージをの部屋のようなものです。パーティション分割を行うことで一つの物理ストレージに複数の領域を作成することができます。
実際にやってみましょう。ここで行う操作はBIOSモードで入っている人とUEFIモードで入っている人で異なります。

=== UEFIモードの場合

パーティションテーブルには複数の種類があり、主にGPTとMBRがあります。
ざっくり説明すると古くてパーティションの数と容量に制限があるのがMBRでその改良版がGPTです。
GPTの場合、作れるパーティション数の制限がなくなり、容量の制限も実質制限がなくなります。
UEFIから起動するようにするにはGPTでパーティション分割する必要があります。
GPTで分割する場合、マニュアルに記載されているfdiskではなくgdiskを用います。
ここではgdiskをわかりやすいUIで使いやすくしたcgdiskを用いていきます。

//emlist[]{ 
cgdisk /dev/sda
//}

このような画面が表示されると思います。
念の為容量の記載を確認してください。間違えて他のストレージを開いてしまっているといったミスがよくあります。


マニュアルのおすすめ通り次のように分割していきます。

分割に成功したら各パーティションのフォーマットをしていきます。

以下のようにフォーマットしていきます。


簡単にそれぞれのフォーマットを説明すると
ext4はLinuxでよく使われるファイルフォーマット、
fat32はUSBなどのリムーバブルディスクによく使われるフォーマット方式です。
EFIパーティションはBIOSが使うもので、BIOSはfat32しか読むことができないため、EFIパーティションはfat32でフォーマットします。

=== BIOSモードの場合

BIOSはGPTパーティションテーブルに対応していないため、MBRパーティションテーブルを採用します。
その際、マニュアル通りfdiskを用いてパーティションを分割していきます。
fdiskは対話型プロンプトでパーティション分割を行うため、cgdiskより使い方がわかりにくいです。
しかし、難しくはないので焦らずにやっていきましょう。

パーティション分割が終わったら以下のようにフォーマットしていきます。
UEFIの場合のときにあったEFIパーティションがなくなってswapと本体だけになってますね。
実際には誤操作やセキュリティ対策で/bootを他パーティションにわけたりしますが、
今回は簡単のため分けません。

それぞれマウントしていきます。

//emlist[]{ 
mount /dev/sda2
swapon /dev/sda1
//}

マウントしたら次に進みます。

== ベースパッケージのインストール

いよいよLinuxをインストールしていきます。
インストールにはpacstrapというコマンドを使っていきます。

//emlist[]{ 
pacstrap -K /mnt linux linux-firmware 
//}