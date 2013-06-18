var win = Titanium.UI.createWindow();

var webView = Ti.UI.createWebView({
    url: 'web.html'
});

webView.addEventListener('load', function(){
    var js =
    "(function () {" +
    "   navigator.cascades.onmessage = function onmessage(message) {\n" +
    "   }\n" +

    "    Ti = {};" +
    "    Ti.API = {};" +
    "    Ti.API.info = function (e) {" +
    "        navigator.cascades.postMessage('Ti.API.info(' + JSON.stringify(e) + ')')" +
    "    };" +
    "    Ti.App = {};" +
    "    Ti.App.addEventListener = function (e, t) {" +
    "        navigator.cascades.postMessage('Ti.App.addEventListener(' + JSON.stringify(e) + ', ' + t + ')')" +
    "    };" +
    "    Ti.App.fireEvent = function (e, t) {" +
    "        t = t || {};" +
    "        navigator.cascades.postMessage('Ti.App.fireEvent(' + JSON.stringify(e) + ', ' + JSON.stringify(t) + ')')" +
    "    }" +
    "})();";
    webView.evalJS(js);
});

win.add(webView);


win.open();


