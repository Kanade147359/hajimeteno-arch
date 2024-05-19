== 付録　Linuxディストリビューションとは

Linuxという言葉には広義の意味と狭義の意味があります。
Linuxディストリビューションの説明をするにはこの狭義の意味を理解している必要があります。
Linuxとは本来Linuxカーネルを指す言葉です。カーネルとはハードウェア制御、ソフトウェアの実行、リソースの管理などを行うOSが行うべき機能を行う部分です。
Linuxはこのカーネルの状態で配布されています。

//indepimage[linux-kernel][Linux Kernel Archive]

しかし、LinuxカーネルだけではOSとして利用することは困難です。
そこで、Linuxカーネルとそれを人が用いるために必要なソフトウェアを組み合わせた形で配布をする様になりました。
このように配布をしているセットをディストリビューションといいます。
Linuxは広義ではLinuxディストリビューションのことを指します。例えばUbuntuは勿論"Linux"です。

Linuxディストリビューションには様々な種類があり、それぞれに独自の目標、思想があります。

ディストリビューションはベースとするディストリビューションによって系統に分けることができます。
それぞれの系統によって使うパッケージマネージャや設定ファイルの名前などに共通点があります。

1. Debian系

//indepimage[Debian][Debianのロゴ]

 Debianというディストリビューションをベースに設計されたディストリビューション郡です。
 最も有名なディストリビューションの一つであるUbuntuはここに分類されます。
 パッケージマネージャはaptを用います。
 Ubuntu、設定ファイル、ネットワークマネージャ等細部が異なります。
 最近はUbuntuをベースとしたディストリビューションが多いため、
 Ubuntu系ディストリビューションは別にまとめたほうがいいかもしれません。

2. RedHat系

//indepimage[Red_Hat][Red Hatのロゴ]

 レッドハット社が販売している業務向け有償ディストリビューション「Red Hat Enterprise Linux(以下RHEL)」と互換性を持つことを目標にしたディストリビューション郡です。
 パッケージマネージャはrpmを用います。RHELを使うにはサブスクリプション契約を行う必要があります。しかし、中小企業や研究室、個人用途のような
 サポートは不要でいいのでとにかくシステムを使いたい、という場面は往々にしてあります。
 この系統のディストリビューションを使っていればRHEL向けのソフトを用いることができます。
 CentOS Linuxの開発終了、サポート終了、RHELのソースコードの非公開化など最近話題に事欠かないディストリビューション郡で、
 利用する際は最新の情報化どうかを確認する必要がありそうです。

3. Arch系

//indepimage[Arch][Arch Linuxのロゴ]

 この本で注目したArch Linuxをベースに設計されたディストリビューション郡です。
 Arch Linuxは自由さこと魅力ですが、システムのメンテナンスや
 面倒な部分を改善することを目標とするディストリビューションが多い気がします。


4. Slackware系

//indepimage[Slackware][Slackwareのロゴ]

Slackwareは最古のLinuxディストリビューションで、非常にシンプルなシステム設計がなされています。
Linuxを素に近い状態からカスタマイズできるので
パッケージマネージャはPkgtoolというものを用いますが、これは依存関係の自動解決は行ってくれません。
Slackelやpuppy LinuxなどのディストリビューションはSlackwareをベースとしていますが、使いやすいようにかなりの魔改造が施されています。

5. Gentoo系

//indepimage[gentoo][Gentooのロゴ]

Gentoo Linuxというディストリビューションをベースに設計されたディストリビューションです。
パッケージマネージャはPortageというものを用います。
このディストリビューションの特徴はパッケージがソースコードで管理されている点にあります。
そのため、パッケージは逐一手元でコンパイルする必要があります。
その利点として多種多様なアーキテクチャに向けて最適化を施すことができ、かなりマイナーなCPUにも対応しています。
(Arch Linuxはx86-64にのみ対応)
因みにChrome OSはGentoo Linuxを魔改造して作られた代物です。
意外とGentoo系のOSは社会に浸透しているのです。

6.　独自系

//indepimage[puppy][Puppy Linuxのロゴ]

Linuxカーネルに独自の改造を施したディストリビューションです。
SolusやKaOSのように目指す目的に沿った独自のパッケージマネージャを備えているディストリビューションや
コンテナのベースになる極小なAlpine LinuxやUSB駆動前提の軽量OSであるEasyOSのように
各分野に特化したOSが多くあります。
また、各系統でベースに使われているディストリビューションも独自系に分類できるでしょう。

以上の区分は私が独自に考えている系統名で公式のものではありません。
どのようなディストリビューションがあるのか、どのようなディストリビューションが人気なのか等、
Linuxディストリビューションの情報がまとまっているサイト@<b>{DistroWatch}(@<href>{https://distrowatch.com/})があります。

//indepimage[DistroWatch][DistroWatchのホーム画面]

DistroWatchにはディストリビューションの検索機能やランキング機能があります。
ランキング機能を見てみるとなんとUbuntuは一位ではありません。
1位はMX LinuxというDebian系のディストリビューションです。
軽くてとても使いやすいデスクトップ志向のディストリビューションですよ。

VirtualBoxのような仮想マシンを用いれば簡単に各ディストリビューションを試すことができます。
ぜひいろいろなディストリビューションに触れてみてください。


