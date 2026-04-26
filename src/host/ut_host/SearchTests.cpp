
    TEST_METHOD(ForwardCaseSensitiveRegex)
    {
        auto& gci = ServiceLocator::LocateGlobals().getConsoleInformation();
        Search s;
        s.Reset(gci.renderData, L"[AB]", SearchFlag::RegularExpression, false);
    }
};
