= Arch Linuxをインストールする

まず公式HPのインストールガイドに沿ってArch Linuxをインストールします。
ここでは最低限起動する状態を目指していきます。

== Wifiにつなげる

早速ノートパソコン
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