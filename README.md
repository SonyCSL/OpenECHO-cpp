OpenECHO-cpp
============

C++ Implementation of ECHONET Lite

###概要

OpenECHO-cppは、家電やセンサーデバイスなど、スマートハウスで用いられる機器のための通信プロトコルである[ECHONET Lite][]をC++で実装したドライバライブラリです。
同Java版の[OpenECHO][]と兄弟的なライブラリになりますが、言語以外にもいくつかの相違点があります。一番大きな違いは、C++版には機器オブジェクトがなく、使う機器のクラスを自分で生成する必要があるということです。面倒さと引き換えに、サイズの小ささを獲得しています。


現在、ECHONET Lite対応機器としてECHONETコンソーシアムに認証された機器のリストが[こちらにあります](http://www.echonet.gr.jp/kikaku_ninsyo/list_lite/equip_srch)。2014年4月時点ですでに160種類以上の機器が受理されている模様です。

※ただし、あくまでコンソーシアムが認証した機器のリストであって、すでに市場に出回っているかどうかはわかりません。OpenECHOもこれら全ての機器の動作を保証するものではありません。というか、どの機器の動作も保証いたしません。

Java版を用いて実装されたAndroidホームサーバー「Kadecot」による[動作実験ビデオ](http://www.youtube.com/watch?v=SwpHSAvoV9I)があります。

###ライセンス
本ソフトウェアの著作権は[株式会社ソニーコンピュータサイエンス研究所][]が保持しており、[MITライセンス][]で配布されています。ライセンスに従い，自由にご利用ください。

###用いているデータベース
本ライブラリの作成には、弊社から公開されている[ECHONET Liteデータベース][]を用いています。
[ECHONET Liteデータベース][]の最新仕様へのアップデート・やフィードバックも随時募集しています。データベースのライセンスはパブリックドメインですのでぜひご協力ください。

###互換性と動作レポート
OpenECHO-cppは標準的なC++の機能だけで実装されておりますが、必ずどこでも動くわけではありません。動作チェックは行っておらず動く保証はありません。ご了承ください。

[ECHONET Lite]: http://www.echonet.gr.jp/ "ECHONET Lite"
[OpenECHO]: https://github.com/SonyCSL/OpenECHO "OpenECHO"
[株式会社ソニーコンピュータサイエンス研究所]: http://www.sonycsl.co.jp/ "株式会社ソニーコンピュータサイエンス研究所"
[MITライセンス]: http://opensource.org/licenses/mit-license.php "MITライセンス"
[Processing]: http://processing.org "Processing"
[神奈川工科大学スマートハウス研究センター]: http://smarthouse-center.org/sdk/ "神奈川工科大学スマートハウス研究センター"
[ECHONET Liteデータベース]: https://github.com/SonyCSL/ECHONETLite-ObjectDatabase "ECHONET Liteデータベース"
