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

## steamのインストール

よくPCでゲームをする方はご存知だと思いますが、Steamは米Valve社が提供しているゲーム配信プラットフォームです。
ゲームの購入とインストールは全てSteam上で行うのでSteamを用意すればすぐにゲームで遊べるようになります。

### multilibリポジトリの有効化

steamはmultilibリポジトリに含まれているため、multilibリポジトリを有効にします。
/etc/pacman.confを開き、[multilib]セクションをアンコメントします。
//emlist[/etc/pacman.confをvimで開く]{
vim /etc/pacman.conf
//}
//emlist[]{
- 
- 

+
+
}
multilibリポジトリには64bit環境で32bitアプリを実行するために必要なソフトウェアが含まれています。
steamは一部32ビットのライブラリに依存しています。また、古いゲームとの互換性を保つために32bitのライブラリが必要です。
そのため、steam

