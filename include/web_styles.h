#ifndef WEB_STYLES_H
#define WEB_STYLES_H

/**
 * @file web_styles.h
 * @brief Feuille de styles CSS pour l'interface web
 * @version 0.6.0
 * 
 * Module dédié à la gestion des styles CSS de l'interface web.
 * Contient tous les styles pour les cartouches, grille responsive, animations, etc.
 */

// CSS pour l'interface web
const char* WEB_STYLES = 
    "* {margin:0;padding:0;box-sizing:border-box;}"
    "body{font-family:'Segoe UI',Arial,sans-serif;background:linear-gradient(135deg,#667eea 0%,#764ba2 100%);min-height:100vh;padding:20px;}"
    ".container{max-width:900px;margin:0 auto;}"
    ".header{text-align:center;color:white;margin-bottom:30px;}"
    ".header h1{font-size:2.5em;margin-bottom:5px;text-shadow:2px 2px 4px rgba(0,0,0,0.3);}"
    ".header p{font-size:1.1em;opacity:0.95;}"
    ".cards-grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(280px,1fr));gap:20px;margin-bottom:20px;}"
    ".card{background:white;border-radius:12px;padding:20px;box-shadow:0 8px 16px rgba(0,0,0,0.1);transition:all 0.3s ease;}"
    ".card:hover{transform:translateY(-5px);box-shadow:0 12px 24px rgba(0,0,0,0.15);}"
    ".card-full{grid-column:1 / -1;}"
    ".card-title{font-size:1.3em;font-weight:bold;margin-bottom:15px;color:#333;border-bottom:2px solid #667eea;padding-bottom:10px;}"
    ".card-item{display:flex;justify-content:space-between;padding:8px 0;border-bottom:1px solid #eee;font-size:0.95em;}"
    ".card-item:last-child{border-bottom:none;}"
    ".card-label{font-weight:600;color:#555;}"
    ".card-value{color:#333;text-align:right;}"
    ".card-value.mono{font-family:monospace;font-size:0.9em;}"
    ".progress-container{margin-top:12px;}"
    ".progress-label{display:flex;justify-content:space-between;font-size:0.85em;margin-bottom:5px;color:#666;}"
    ".progress-bar{background:#e0e0e0;height:10px;border-radius:5px;overflow:hidden;}"
    ".progress-fill{background:linear-gradient(90deg,#667eea,#764ba2);height:100%;transition:width 0.3s;}"
    ".actions{display:flex;gap:10px;justify-content:center;flex-wrap:wrap;margin-top:30px;}"
    "button{background:linear-gradient(135deg,#667eea,#764ba2);color:white;border:none;padding:12px 24px;border-radius:6px;cursor:pointer;font-size:1em;font-weight:600;transition:all 0.3s;}"
    "button:hover{transform:scale(1.05);box-shadow:0 4px 12px rgba(102,126,234,0.4);}"
    "button.danger{background:linear-gradient(135deg,#f093fb,#f5576c);}"
    "button.danger:hover{box-shadow:0 4px 12px rgba(245,87,108,0.4);}"
    ".signal-bar{display:inline-block;width:12px;height:12px;border-radius:2px;background:#667eea;margin-right:3px;}"
    ".signal-bar.active{background:#4CAF50;}";

#endif // WEB_STYLES_H
