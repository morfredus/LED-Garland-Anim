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
    "body{font-family:'Segoe UI',Arial,sans-serif;background:linear-gradient(135deg,#d32f2f 0%,#e53935 25%,#fbc02d 60%,#43a047 100%);min-height:100vh;padding:24px;}"
    ".container{max-width:900px;margin:0 auto;}"
    ".header{text-align:center;color:white;margin-bottom:30px;}"
    ".header h1{font-size:2.6em;margin-bottom:6px;text-shadow:2px 2px 6px rgba(0,0,0,0.35);}"
    ".header p{font-size:1.1em;opacity:0.95;}"
    ".cards-grid{display:grid;grid-template-columns:repeat(auto-fit,minmax(280px,1fr));gap:20px;margin-bottom:20px;}"
    ".card{background:white;border-radius:14px;padding:20px;box-shadow:0 10px 18px rgba(0,0,0,0.12);transition:all 0.3s ease;border:2px solid #fbc02d;}"
    ".card:hover{transform:translateY(-4px);box-shadow:0 14px 26px rgba(0,0,0,0.18);}"
    ".card-full{grid-column:1 / -1;}"
    ".card-title{font-size:1.35em;font-weight:bold;margin-bottom:15px;color:#b71c1c;border-bottom:3px dashed #fbc02d;padding-bottom:10px;}"
    ".card-item{display:flex;align-items:center;justify-content:space-between;padding:10px 0;border-bottom:1px solid #eee;font-size:0.98em;}"
    ".card-item:last-child{border-bottom:none;}"
    ".card-label{font-weight:700;color:#1b5e20;}"
    ".card-value{color:#333;text-align:right;}"
    ".card-value.mono{font-family:monospace;font-size:0.95em;}"
    "select,input{padding:8px;border-radius:8px;border:1px solid #ddd;}"
    ".actions{display:flex;gap:10px;justify-content:center;flex-wrap:wrap;margin-top:20px;}"
    "button{background:linear-gradient(135deg,#b71c1c,#e53935);color:white;border:none;padding:10px 18px;border-radius:8px;cursor:pointer;font-size:1em;font-weight:700;transition:all 0.25s;}"
    "button:hover{transform:scale(1.05);box-shadow:0 6px 14px rgba(229,57,53,0.35);}"
    "button.danger{background:linear-gradient(135deg,#6a1b9a,#8e24aa);}"
    "button.danger:hover{box-shadow:0 6px 14px rgba(142,36,170,0.35);}"
    "button.apply{background:linear-gradient(135deg,#43a047,#66bb6a);margin-left:10px;padding:8px 12px;}";

#endif // WEB_STYLES_H
