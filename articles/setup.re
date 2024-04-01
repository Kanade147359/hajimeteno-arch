= 執筆環境を整える

== 前提とする環境

これからの説明はVSCodeでの執筆を前提としています。
また、dockerをインストールしておきましょう。
Windows環境を使っている方はWSLでUbuntuを使い、その上でvscodeを起動させるのがおすすめです。


== 環境構築

おとなしくdockerを使いましょう。どうしても手元に作りたいという人はぜひ挑戦してみましょう。

@<href>{https://github.com/TechBooster/ReVIEW-Template}

に環境構築方法がかいてありますが、多分うまくいきません。

vscodeの場合、Dev Containerの拡張機能を有効にしておけば、このファイルを開いたときに自動的にコンテナを立ち上げて
コンテナの中に入ってくれます。
ターミナルを開いて

//emlist[]{
root@573d4ac95ebf:/workspaces/ReVIEW-Tutrial/articles# 
//}
のように表示されるようになればコンテナに入っています。

dockerコンテナに入れない場合でもdockerをインストールした状態で

//emlist[]{
./build-in-docker.sh
//}

または

//emlist[]{
sudo ./build-in-docer.sh
//}

とすればarticlesディレクトリ内にコンパイル済みのpdfが出来上がります。
ちょっと時間かかるけどね