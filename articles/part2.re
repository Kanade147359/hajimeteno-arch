= Arch Linuxをインストールする

まず公式HPのインストールガイドに沿ってArch Linuxをインストールします。
ここでは最低限起動する状態を目指していきます。

尚最近は簡単にArch Linuxをインストール出来るarchinstallというコマンドがインストーラーに導入されました。
しかし、今回はこれを使わずに手動でインストールしていきます。
archinstallコマンドで簡単にインストールしてしまうとシステムの内容がブラックボックスになり、
管理がしにくくなると感じているためです。


== インストールメディアの作成

まず、インストールメディアを作成します。USBメモリを用意してください。
DVDドライブのあるノートパソコンであればDVDに焼いても問題ありません。
今回はインストールディスクを作成する二種類の方法を紹介します。

1. rufusを使う(Windowsユーザ向け)

rufusはブート可能なUSBドライブを簡単に作ることができるWindowsソフトです。
rufusのダウンロードページ@<href>{https://rufus.ie/ja/}からダウンロードしてください。

//indepimage[rufus-download][rufusのダウンロードページ]

64bitパソコンを使っている人が殆どかと思いますので
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
//cmd{ 
# ls /sys/firmware/efi/efivars
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

//cmd{
# iwctl
//}

以下のような表示になればOKです。

//cmd{
[iwd]#
//}

対話型プロンプトから出て、ネットワーク疎通を確認しましょう。
//cmd{ 
[iwd]# exit
# ping www.archlinux.jp
//}

ネットワークに繋がっていることを確認したら次に進みましょう。

== パーティション分割〜マウントまで

次にインストールするドライブのパーティション分割をし、各パーティションをフォーマットします。
パーティションとはHDDやSSDのようなストレージをの部屋のようなものです。パーティション分割を行うことで一つの物理ストレージに複数の領域を作成することができます。
実際にやってみましょう。

まず認識されているディスクを確認しましょう。以下のようにfdisk -lで確認ができます。

//cmd{ 
# fdisk -l
//}

Linuxにおいてハードディスクのようなデバイスは/devディレクトリの下にファイルとして表示され、通常のファイルと同様に扱うことができます。
表示された/dev/sd-か/dev/nvme-のデバイスがHDDやSSDです。/dev/loop0のようなファイルは無視して問題ありません。
容量を確認して、実際にインストールしたいドライブであるかどうかを確認しておきましょう。間違ったドライブへのインストールを行うと取り返しがつきません…。
自分の場合、/dev/sdaだったので以下からのコマンドにおいてデバイスファイルは/dev/sdaを用います。
各自の環境に合わせて使うコマンドを変えてください。

以下から行う操作はBIOSモードで入っている人とUEFIモードで入っている人で異なります。

== UEFIモードの場合

パーティションテーブルには複数の種類があり、主にGPTとMBRがあります。
ざっくり説明すると古くてパーティションの数と容量に制限があるのがMBRでその改良版がGPTです。
GPTの場合、作れるパーティション数の制限がなくなり、容量の制限も実質制限がなくなります。
UEFIから起動するようにするにはGPTでパーティション分割する必要があります。
GPTで分割する場合、マニュアルに記載されているfdiskではなくgdiskを用います。
ここではgdiskをわかりやすいUIで使いやすくしたcgdiskを用いていきます。

//cmd{ 
# cgdisk /dev/sda
//}

このような画面が表示されると思います。

//indepimage[][]

作成するパーティションと各パーティションのフォーマットは以下のとおりです。

//table[UEFI-partition][UEFIの際のパーティション構成例]{
    マウントポイント	パーティション  パーティションタイプ    容量
    /mnt/boot   /dev/sda1   EFI system partition 512MB
    [swap]  /dev/sda2   Linux swap  4GB
    /mnt    /dev/sda3   Linux x86-64 root    残り容量すべて 
    -----------------
//}

EFI system partitionはUEFIが起動時はじめに読み込む領域です。
後、ブートローダをこの領域にインストールするように、OSの起動に必要なシステムを含む大切な領域です。
swap領域とはメモリが足らなくなったときに不具合を防ぐためにメモリ代わりに使用される領域です。
昔は物理メモリが少なかったためメモリ量の2倍量指定することが望まれましたが、現在のパソコンはメモリが多いためそこまでの領域を指定する必要はありません。
4GB、8GB程度設定しておけば十分だと思います。
/dev/sda3にLinuxのルートをインストールします。

まず、EFIパーティション用のパーティションを作成します。
free spaceにカーソルをあわせて下のメニューより"New"を選んでください。
First sectorは空欄で構いません。
EFIパーティションは最低300MBあることが望ましいため、余裕を持って512MBに分けます。
Hex codeはFat32では0700を指定します。
パーティションの名前はつけなくて構いません。任意ですのでわかりにくいと感じたらわかり易い名前をつけても良いです。
こうすると512MBのパーティション1が設定されます。

以下は操作をまとめたものです。空欄は何も入力せずにEnterを押してください。
//cmd{
First sector (2048-268435422, default = 2048): 
Size in sectors or {KMGTP} (default = 268431360): 512M
Hex code or GUID (L to show codes, Enter = 8300): 0700
Enter new partition name, or <Enter> to use the current name:
//}

間違えたパーティションを作ってしまっても焦らず"Delete"で消してください。"Write"を選択するまではパーティションは作成されません。

次にswap用パーティションを作成します。

//cmd{
First sector (1050624-268435422, default = 1050624): 
Size in sectors or {KMGTP} (default = 267382784): 4G
Hex code or GUID (L to show codes, Enter = 8300): 8200
Enter new partition name, or <Enter> to use the current name:
//}

最後にLinuxの本体をインストールするパーティションを作成します。
残りの全ての領域を指定するため、サイズの欄は空欄でEnterを押します。

//cmd{
First sector (9439232-268435422, default = 9439232): 
Size in sectors or {KMGTP} (default = 258994176): 
Hex code or GUID (L to show codes, Enter = 8300): 
Enter new partition name, or <Enter> to use the current name:
//}

ここまでできたらWriteを選択して実際にパーティションを作成します。
パーティションを作成したら"Quit"で退出しましょう。

分割に成功したら各パーティションのフォーマットをしていきます。

@<b>{mkfs}というコマンドを用いて以下のようにフォーマットしていきます。

//cmd{
# mkfs.fat -F 32 /dev/sda1 #fat32にフォーマット
# mkswap /dev/sda2 #swap領域を作成
# mkfs.ext4 /dev/sda3 #ext4に作成
//}

簡単にそれぞれのフォーマットを説明します。
ext4はLinuxでよく使われるファイルフォーマットです。
fat32はUSBなどのリムーバブルディスクによく使われるフォーマット方式です。
UEFIはfat32しか読むことができないため、EFIパーティションはfat32でフォーマットします。

最後にそれぞれのファイルシステムをマウントします。
EFIシステムパーティションをマウントするとき、/mnt/bootが元々存在しないので--mkdirオプションを忘れないようにしましょう。

//cmd{
# mount /dev/sda2 /mnt
# mount --mkdir /dev/sda1 /mnt/boot
# mkswap /dev/sda1
//}

ここまでできたらシステムのインストールに進んでください。

=== BIOSモードの場合

BIOSはGPTパーティションテーブルに対応していないため、MBRパーティションテーブルを採用します。
その際、マニュアル通りfdiskを用いてパーティションを分割していきます。
fdiskは対話型プロンプトでパーティション分割を行うため、cgdiskより使い方がわかりにくいです。
しかし、難しくはないので焦らずにやっていきましょう。
以下のように分割、フォーマットしていきます。

//table[UEFI-partition][UEFIの際のパーティション構成例]{
    マウントポイント	パーティション  パーティションタイプ    容量
    -----------------
    [swap]  /dev/sda1   Linux swap  4GB
    /mnt    /dev/sda2   Linux x86-64 root   残り容量すべて 

//}
UEFIモードの場合と比べるとEFI system partitionがなくシンプルな構成になっています。
実際に分割していきましょう。

//cmd{
# fdisk /dev/sda
//}

すると対話型プロンプトに入ります。@<b>{m}でヘルプを表示します。
ヘルプを表示すると一文字のコマンド達の説明が羅列します。よくわからなくなったらヘルプを読みましょう。
@<b>{n}で新しいパーティションを作成できます。
Partition number、First sectorはデフォルトの値でよいので空欄でEnterを押してください。
Last sectorの欄で実際のサイズを指定します。4GBのパーティションを作成する際は"+4G"と入力します。頭の+を忘れがちなので注意しましょう。
こうすると新しいパーティションができます。もう一つのパーティション(Linux x86-64 root)は全て空欄で作成してください。
@<b>{p}で設定したパーティションを確認できます。
設定が間違えていなかったら@<b>{w}でパーティションを実際に書き込みます。書き込み終わったら@<b>{q}で出ます。

分割に成功したら各パーティションのフォーマットをしていきます。

@<b>{mkfs}というコマンドを用いて以下のようにフォーマットしていきます。

//cmd{
# mkswap /dev/sda1 #swap領域を作成
# mkfs.ext4 /dev/sda2 #ext4に作成
//}

それぞれのファイルシステムをマウントします。

//cmd{
# mount /dev/sda2 /mnt
# mkswap /dev/sda1
//}

ここまで終わったらシステムのインストールに移動しましょう。

== ベースパッケージのインストール

いよいよLinuxをインストールしていきます。
インストールにはpacstrapというコマンドを使っていきます。
baseパッケージとlinuxカーネル、ファームウェアをインストールしていきます。

//cmd{ 
# pacstrap -K /mnt base linux linux-firmware 
//}

これらのパッケージをインストールすると最低限Linuxとして動く状態を作ることができます。

== システムの設定

Linuxシステムの準備ができたので実際にその環境に入ってシステムの設定を行っていきます。

=== /etc/fstabの生成

その際に、/etc/fstabというファイルが必要になるため、システムに入る前に作成していきます。
fstabは起動時マウントするデバイスを指定する重要なファイルです。
このファイルの設定がないと/bootやswap領域が使えないため、必ず設定します。
fstabの設定は手動で書くこともできますが、少し面倒です。ここで@<b>{genfstab}という自動でfstabを作ってくれる便利なコマンドを使います。
以下のコマンドを実行すると/etc/fstabが自動生成されます。とても便利。

//cmd{
# genfstab -U /mnt >> /mnt/etc/fstab
//}

//indepimage[][]

=== chroot

/etc/fstabを作成したらシステムに入っていきます。
システムに入るときは@<b>{chroot}というコマンドを使います。chrootは一時的に指定したディレクトリを新しくルートディレクトリに変更して操作する環境を変えるコマンドです。
この変更された環境は@<b>{chroot監獄}というらしいです。
直接chrootを使うと/procのようなシステムファイルのマウント、ネットワーク設定の引き継ぎなどの設定を行う必要があり、とても面倒です。
そこで@<b>{arch-chroot}というコマンドを使います。以下のようにarch-chrootを実行すると/mntにインストールした新しいシステムに操作対象を変更できます。

//cmd{
# arch-chroot /mnt
//}

すると

//cmd{
[root@archiso /]#
//}

という表示になると思います。
このような表示になればchroot成功です。

=== タイムゾーンの変更

以下のコマンドを入力してタイムゾーンを設定してください。日本に住んでいる方はタイムゾーンをAsia/Tokyoに指定します。

//cmd{
# ln -sf /usr/share/zoneinfo/Asia/Tokyo /etc/localtime
//}

ちなみにln -sはシンボリックリンク(Windowsでいうショートカット)を作成するコマンドです。
このコマンドは/etc/localtimeという名前のAsia/Tokyoへのシンボリックリンクを作成します。

以下のコマンドで時刻を調整するファイル/etc/adjtimeを作成します。

//cmd{
# hwclock --systohc
//}

==　ロケール設定

次にロケールを設定します。ロケールを設定するとき、ファイルの内容を直接書き換える必要があり、テキストエディタが必要になります。
標準でviというテキストエディタはインストールされていますが、使い方にクセがあるため、新たにテキストエディタをダウンロードします。
なんでもよいのですが、CLI上で動作するテキストエディタが初めて、という方はnanoが一番直感的でわかりやすいと思います。
nanoをインストールしていきましょう。インストールするときは@<b>{pacman}を使います。

pacmanはArch LinuxのパッケージマネージャでArch Linuxの最も重要な機能の一つです。
パッケージマネージャとはアプリを必要なファイルを集めた「パッケージ」として管理し、各パッケージの依存関係の確認を行ってくれるアプリです。
Windowsにはwinget、macOSにはHomebrew、Ubuntuにはaptというパッケージマネージャがあります。
以下のようなコマンドでnanoをインストールします。

//cmd{
# pacman -S nano
//}

パッケージのインストールの際は-Sオプションをつけます。
これでnanoがインストールされました。尚、後からもchroot下で追加でパッケージを入れていきますが、先程のbaseパッケージと同じタイミングでpacstrapでインストールしても問題ありません。

/etc/locale.genを編集し、"en_US.UTF-8 UTF-8"と"ja_JP.UTF-8 UTF-8"が書かれた行をアンコメントします。以下のコマンドで/etc/locale.genをnanoで開きます。

//cmd{
# nano /etc/locale.gen
//}

つまり行頭の#を消してください。

//emlist[]{
- #en_US.UTF-8 UTF-8
- #ja_JP.UTF-8 UTF-8

+ en_US.UTF-8 UTF-8
+ ja_JP.UTF-8 UTF-8
//}

編集が終わったら保存し、以下のコマンドを実行します。

//cmd{
# locale-gen
//}

次に/etc/locale.confを作成します。jpに設定したくなりますが、日本語フォントがインストールされていないため、jpに設定すると文字が化けて全く読めなくなります。
そのため、CLI環境はen_US.UTF-8に設定しておきましょう。
存在しないファイルをnanoで指定すると新しいファイルを作ることができます。

//cmd{
# nano /etc/locale.conf
//}

以下の一行を書きます。

//emlist[]{
LANG=en_US.UTF-8
//}

次にキーマップを指定します。
/etc/vconsole.confを作成して次の一行を書きます。

//emlist[]{
KEYMAP=jp106
//}

== ネットワーク設定

ネットワークの設定を行います。
まずホストネームを指定します。
/etc/hostnameファイルを作成してホストの名前をファイルに追記すると指定ができます。
私はArch-laptopとしますが、好きな名前をつけてあげてください。

//emlist[]{
Arch-laptop
//}

次にNetworkManagerをインストールしていきます。
NetworkManagerはシステムがネットワークに自動的に接続て切るようにするためにネットワークの検出と設定の機能を提供するプログラムです。
NetworkManagerのような、ネットワーク設定を行うパッケージをインストールしないままシステムを起動すると、インターネットに繋がらない(有線ですらも)文鎮が出来上がるので必ず入れておきましょう。

//cmd{
# pacman -S networkmanager
//}

インストールしたらシステム起動時自動的に起動するように設定します。

//cmd{
# systemctl enable　NetworkManager
//}

サービス名は大文字混じり、パッケージ名は小文字のみです。紛らわしいですが、注意しましょう。

ここまで設定しておけばシステム起動後ネットワーク設定ができるようになります。

== ユーザーの設定

パスワードの設定をしましょう。以下のコマンドで設定するパスワードはrootユーザ(特権ユーザ)のパスワードです。

//cmd{
# passwd
//}

次に一般ユーザを作っていきます。今までは何でもできるrootユーザで設定をしてきました。
しかし、普段遣いをするときに常にrootユーザを使っているとふとした手違いでシステムを破壊し再起不能になる可能性があります。
そのため、権限を制限した一般ユーザを新たに作っておき、再起動後は一般ユーザで操作を続けることにします。

一般ユーザ"kanade"を作成します。各自自分の好きなユーザーネームでユーザを作成してください。
-mを付けるとそのユーザのホームディレクトリを自動で作ってくれます。

//cmd{
# useradd -m kanade
//}

一般ユーザはシステムの変更ができません。つまり、pacmanによるパッケージのインストールも出来ません!
...それでは不便なので一般ユーザでも一時的にrootの力を振りかざすことができる@<b>{sudo}コマンドをインストールしておきましょう。

//cmd{
# pacman -S sudo
//}

Ubuntuユーザなら"sudo apt update"でおなじみのsudo君です。
以下のように実行したいコマンドの頭にsudoを付けると一時的にrootの権限で実行することができます。

//cmd{
$ sudo @<b>{任意のコマンド}
//}

しかし、誰も彼もsudoが使えるわけではなく、ユーザはsudoersに追加されている必要があります。
sudoersは/etc/sudoersを編集することで追加することができます。このファイルを直接指定することは推奨されず、@<b>{visudo}というコマンドでこのファイルを開きます。
しかし、visudoはデフォルトでviを開き出すので以下のようにEDITOR変数を変更することでnanoで開くように設定します。

//cmd{
# export EDITOR=nano
//}

そうしたらvisudoで/etc/sudoersを開きます。

//cmd{
# visudo
//}

以下に表すような行に内容を加えます。ユーザ名は各自変更してください。

//emlist[]{
- root ALL=(ALL:ALL) ALL 

+ root ALL=(ALL:ALL) ALL 
+ kanade ALL=(ALL:ALL) ALL
//}

保存をするとkanadeユーザがsudoを使えるようになります。
最後に一般ユーザのパスワードを設定しましょう。

//cmd{
# passwd kanade
//}

これでユーザの設定は完了です。

== ブートローダの設定

最後にブートローダをインストールしましょう。
ブートローダとはUEFI(BIOS)によって起動されるOSを立ち上げるプログラムです。

電源が入ってからOSが立ち上がるまでの流れを簡単に図に表すと以下の様になります。

//indepimage[][]

GRUBを設定しないままシステムを起動しようとしてもOSは立ち上がりません。
忘れずに設定をしましょう。

Linuxでよく使われるブートローダとしてGRUBがあります。
今回はGRUBをインストールし、設定を進めていきます。

まず、pacmanでgrubパッケージをインストールします。

//cmd{
# pacman -S grub
//}

これからUEFIモードで起動している方とBIOSモードで起動している人で設定が変わります。

=== UEFIモードの場合

追加でefibootmgrをインストールします。

//cmd{
# pacman -S efibootmgr
//}

以下の様なコマンドを実行することでGRUBをシステムにインストールすることができます。

//cmd{
# grub-install --target=x86_64-efi --efi-directory=/boot --bootloader-id=GRUB
//}

設定が完了したら最後に設定ファイルを生成します。
grub-mkconfigを使って/boot/grub/grub.cfgを生成します。

//cmd{
# grub-mkconfig -o /boot/grub/grub.cfg
//}

この設定ファイルを生成するとGRUBはArch Linuxのカーネルを起動するように自動で設定が追加されます。
これでGRUBの設定は終わりです。

=== BIOSモードの場合

以下のコマンドを用いてシステムにGRUBをインストールします。

//cmd{
# grub-install --target=i386-pc /dev/sda
//}

不自然に思うかもしれませんが、--target=i386-pcは実際のCPUがどのような種類でもこのように指定します。
また、/dev/sdaの部分は実際のデバイスファイルの名前に置き換えてください。
@<b>{パーティション名ではなくデバイスファイル名です。注意してください。}

インストールしたら、設定ファイルの作成を行います。

//cmd{
# grub-mkconfig -o /boot/grub/grub.cfg
//}

この設定ファイルを生成するとGRUBはArch Linuxのカーネルを起動するように自動で設定が追加されます。
これでGRUBの設定は終わりです。

== 再起動

お疲れ様でした。インストールの完了です。

再起動して無事にArch Linuxが立ち上がることを確認してください。
rebootをする前にexitでchroot環境から抜ける事を忘れないようにしましょう。

//cmd{
# exit # chroot監獄から抜ける
# reboot # 再起動
//}

再起動後、先程作った一般ユーザでログインしましょう。
無事にログインができたら完了です。次の章に進みます。

== 起動しなかった場合

GRUBの設定など、重要な設定を忘れている可能性があります。
このような場合でも慌てず、再度インストールディスクから起動し、インストール作業を再開してください。
既にシステムはインストールしてあると思いますので、
各パーティションをマウントすることで再度chroot環境に入り、設定し直すことができます。

上手く起動しましたら、次の章でデスクトップ環境をインストールしていきます！

