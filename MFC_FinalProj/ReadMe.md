選課小幫手 CoursePickingHelper 專案概觀
===============================================================================

這個檔案包含一份摘要，簡要說明構成 CoursePickingHelper 應用程式的所有檔案，它們個別的內容。

 * `MFC_FinalProj.cpp / MFC_FinalProj.h`
    * The program automatically generated. The start of the APP.

 * `MFC_FinalProjDlg.cpp / MFC_FinalProjDlg.h`
    * The main dialog. It handles with every input data from any dialog that has sent the data and start the corresponding programs.
    * `void import();`: import the course imformation from a json file
    * `void add_class(int cho);`: add a course to table accroding to `cho` of the index of the course
    * `void update();`: update the credit (學分數) on the title
    * `afx_msg void OnCbnSelchangeUnset();`: unselect a course
    * `afx_msg void OnBnClickedImportSave();`: save selected course to a json
    * `afx_msg void OnNMClickClassTable(NMHDR *pNMHDR, LRESULT *pResult);`: show the course codes of selected courses

 * `ClockChange.cpp / ClockChange.h`
    * These files are associated to the file change dialog. Its function is to change old clock data into new clock data.

 * `ClockSet.cpp / ClockSet.h`
    * These files are associated to the “加入鬧鐘” dialog. The function is like ClockChange but it adds a new clock. The ClockChange edit a current existing clock.

 * `ClockMain.cpp / ClockMain.h`
    * These files are associated with the “鬧鐘設定” dialog. It can decide how to show in this dialog, and what to do when you click the button like “修改鬧鐘” on it. Last but not least, it will send the clock data to main dialog.

 * `CountDown.cpp / CountDown.h`
    * These files are associated with the Countdown timer setting dialog. The data input from the dialog will be sent to main dialog.

 * `CMCI.cpp / CMCI.h`
    * These files are associated with the music file playing. By using the MCI (Media Control Interface) functions provided by Windows, you can easily play any media file as you wish.

 * `ShutDown.cpp / ShutDown.h`
    * These files are associated with Shutdown time setting dialog. The data input from this dialog will send to main dialog.

 * `ConfirmBox.cpp / ConfirmBox.h`
    * A yes/no question dialog

 * `Course.cpp / Course.h`
    * a course information structure class
    * `void to_list(CListCtrl* listView,short* class_table,short value,bool unset = false);`: add/remove the course itself to the table (including backend `class_table` and front-end `listView`)
    * `CString toString();`: get the full information of the course
    * `CString toCodeStr();`: get the code and the title of the course
    * `CString* utf8ToCString(char* utf8str)`: **important!**
        * usually a Json use utf8 to encode (most of internet exchanging file use this encoding), so I need to convert to unicode in order to work (display chinese...)

 * `Course_time.cpp / Course_time.h`
    * a time inteval of a course structure class

 * `MFC_FinalProj.vcxproj`
    * 這是使用應用程式精靈所產生之 VC++ 專案的主要專案檔。它含有產生該檔案之 Visual C++ 的版本資訊，以及有關使用應用程式精靈所選取之平台、組態和專案功能的資訊。

 * `MFC_FinalProj.vcxproj.filters`
    * 這是使用應用程式精靈所產生之 VC++ 專案的篩選檔。檔案中含有您專案中檔案與篩選器之間關聯的相關資訊。這項關聯用於 IDE 中以顯示特定節點下具有類似副檔名之檔案的群組 (例如，".cpp" 檔案會與 "Source Files" 篩選器相關聯)。

 * `MFC_FinalProj.rc`
    * 這是程式所用的所有 Microsoft Windows 資源的列表。它含有儲存在 RES 子目錄中的圖示、點陣圖和游標。您可以直接在 Microsoft Visual C++ 內編輯這個檔案。您的專案資源是在 1028。

 * `res\Icon.ico`
    * 這是用來做為應用程式圖示的圖示檔。這個圖示是包含在主要資源檔 MFC_FinalProj.rc 中。

 * `res\MFC_FinalProj.rc2`
    * 這個檔案包含 Microsoft Visual C++ 無法編輯的資源。您應該將所有資源編輯器無法編輯的資源放到這個檔案。


--------------------------

應用程式精靈會建立一個對話方塊類別：  

 * `MFC_FinalProjDlg.h / MFC_FinalProjDlg.cpp` - 對話方塊
    * 這些檔案包含您的 CMFC_FinalProjDlg 類別。這個類別會定義應用程式主對話方塊的行為。對話方塊的範本是在可於 Microsoft Visual C++ 編輯的 MFC_FinalProj.rc 中。

--------------------------

其他功能：  

 * ActiveX 控制項
    * 應用程式包括使用 ActiveX 控制項的支援。

--------------------------

其他標準檔案：  

 * `StdAfx.h, StdAfx.cpp`
    * 這些檔案是用來建置名為 MFC_FinalProj.pch 的先行編譯標頭 (PCH) 檔，以及名為 StdAfx.obj 的先行編譯型別檔。

 * `Resource.h`
    * 這是標準標頭檔，它定義新的資源 ID。Microsoft Visual C++ 會讀取和更新這個檔案。

 * `MFC_FinalProj.manifest`
    * Windows XP 會使用應用程式資訊清單檔案來描述特定並存組件版本的應用程式相依性。載入器會使用這項資訊載入組件快取中的適當組件，或應用程式中的私用組件。應用程式資訊清單可能隨附用於轉散發，做為與應用程式可執行檔相同資料夾中所安裝的外部 .manifest 檔案，或是以資源的形式隨附在可執行檔中。

--------------------------

其他注意事項：  

應用程式精靈使用 "TODO:" 來指示您應該加入或自訂的原始程式碼部分。  
如果您的應用程式使用 MFC 的共用 DLL，您將需要轉散發 MFC DLL。如果您的應用程式採用不同於作業系統地區設定的語言，您還必須轉散發對應的當地語系化資源 mfc110XXX.DLL。  
如需這兩個主題的詳細資訊，請參閱 MSDN 文件中轉散發 Visual C++ 應用程式的章節。  
