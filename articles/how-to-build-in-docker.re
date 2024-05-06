= dockerを用いたRe:VIEWコンパイル方法

Unixシステム(mac, Linux)を前提としている。WindowsではWSL使ってください

== dockerのインストール

後使うbuild-in-docker.sh内でdockerを使うのでインストールをしておいてください

== ReVIEW-Templateのクローン

ReVIEW-Templateというレポジトリがあるのでそれをありがたく使わせてもらう
//emlist[]{
git clone https://github.com/TechBooster/ReVIEW-Template.git
//}
クローンしたら入る
//emlist[]{
cd ReVIEW-Template
//}
== articles/catalog.ymlの編集

コンパイルするファイル名をここにまとめます
テスト用記事が用意されてるので動作が気になるならそのままコンパイルして

== dockerを使ったコンパイル

以下のコマンドでコンパイルできる
//emlist[]{
sudo ./build-in-docker.sh
//}

このコマンドは一時的にdockerコンテナを立ててその中でコンパイルをして出力してくれる

