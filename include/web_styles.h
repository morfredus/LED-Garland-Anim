#ifndef WEB_STYLES_H
#define WEB_STYLES_H

/**
 * @file web_styles.h
 * @brief Feuilles de style pour l'interface web
 * @version 4.0.0
 * @date 2026-01-06
 *
 * Module dédié à la gestion des styles CSS de l'interface web.
 * Contient tous les styles pour les cartouches, grille responsive, animations, etc.
 */

// CSS pour l'interface web
static constexpr const char* WEB_STYLES =
    "* {margin:0;padding:0;box-sizing:border-box;}"
    "body{font-family:'Segoe UI',Arial,sans-serif;background:linear-gradient(135deg,#d32f2f 0%,#e53935 25%,#fbc02d 60%,#43a047 100%);min-height:100vh;padding:24px;padding-top:80px;}"
    "#notification-bar{position:fixed;top:0;left:0;right:0;height:60px;background:white;box-shadow:0 4px 10px rgba(0,0,0,0.15);z-index:9999;display:flex;align-items:center;justify-content:center;border-bottom:3px solid #fbc02d;}"
    "#notification-bar.hidden{display:none;}"
    ".notification-content{padding:0 20px;font-weight:bold;font-size:1.05em;text-align:center;word-break:break-word;max-width:100%;}"
    ".notification-content.success{color:#1b5e20;background:rgba(232,245,233,0.5);}"
    ".notification-content.error{color:#c62828;background:rgba(255,235,238,0.5);}"
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
    "button.apply{background:linear-gradient(135deg,#43a047,#66bb6a);margin-left:10px;padding:8px 12px;}"
    ".radio-grid{display:grid;grid-template-columns:repeat(2,1fr);gap:8px;margin-top:10px;}"
    "@media (max-width:600px){.radio-grid{grid-template-columns:1fr;}}"
    ".radio-item{display:flex;align-items:center;padding:6px 10px;background:#f9f9f9;border:2px solid #e0e0e0;border-radius:8px;cursor:pointer;transition:all 0.2s;min-height:38px;}"
    ".radio-item:hover{background:#e8f5e9;border-color:#43a047;}"
    ".radio-item input[type='radio']{margin-right:8px;cursor:pointer;width:16px;height:16px;flex-shrink:0;}"
    ".radio-item input[type='radio']:checked + label{font-weight:bold;color:#1b5e20;}"
    ".radio-item.selected{background:#e8f5e9;border-color:#43a047;border-width:2px;}"
    ".radio-item label{cursor:pointer;flex:1;font-size:0.95em;user-select:none;}"
    ".section-label{display:block;font-weight:700;color:#1b5e20;margin-top:15px;margin-bottom:5px;font-size:1em;}"
    ".view-toggle{display:flex;align-items:center;justify-content:flex-end;gap:10px;margin-top:10px;}"
    ".toggle-label{color:white;font-weight:700;}"
    ".switch{position:relative;display:inline-block;width:52px;height:28px;}"
    ".switch input{opacity:0;width:0;height:0;}"
    ".slider{position:absolute;cursor:pointer;top:0;left:0;right:0;bottom:0;background:#ccc;transition:.2s;border-radius:28px;}"
    ".slider:before{position:absolute;content:'';height:22px;width:22px;left:3px;bottom:3px;background:white;transition:.2s;border-radius:50%;}"
    ".switch input:checked + .slider{background:linear-gradient(135deg,#43a047,#66bb6a);}"
    ".switch input:checked + .slider:before{transform:translateX(24px);}"
    "body.compact-mode{padding:16px;padding-top:72px;}"
    "body.compact-mode .container{max-width:1100px;}"
    "body.compact-mode .card{padding:14px;border-radius:10px;box-shadow:0 8px 14px rgba(0,0,0,0.1);}"
    "body.compact-mode .card-title{font-size:1.1em;margin-bottom:10px;}"
    "body.compact-mode .radio-grid{grid-template-columns:repeat(auto-fit,minmax(180px,1fr));gap:6px;}"
    "body.compact-mode .radio-item{padding:4px 8px;min-height:32px;}"
    "body.compact-mode .section-label{margin-top:10px;margin-bottom:4px;font-size:0.95em;}"
    "body.compact-mode button{padding:8px 14px;font-size:0.95em;}"
    "body.compact-mode .actions{gap:6px;}"
    "body.compact-mode .header h1{font-size:2.2em;}"
    "body.compact-mode .toggle-label{color:#e8f5e9;}";

#endif // WEB_STYLES_H
